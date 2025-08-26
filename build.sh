#!/bin/bash

# This file is a part of Nitisa framework
# Copyright © 2021 Nitisa. All rights reserved.
# Author: Dimitry Lysenko
# Site: http://nitisa.com
# Download: http://nitisa.com/downloads
# Documentation: http://nitisa.com/documentation
# License: http://nitisa.com/site/license

# Note: this file is allowed to be modified if you wish to build your projects with another set of options,
# which means you have to build Nitisa core and packages with the same set of options.

# Current directory should be the script location directory, like ~/projects/Nitisa/9.0.0

PROJECT=$1 # Project name, like Nitisa, Standard
CONFIGURATION=$2 # Debug and Release are only supported ones
PLATFORM=$3 # x86 and x64 are only supported ones
BRANCH=$4
PROJECT_DIR=$5 # Relative to the current directory, like Packages/Standard

WORK_PATH="$PWD/$PROJECT_DIR"

OPTIONS="-std=c++17 -I $PWD -I $WORK_PATH -I $PWD/Packages"
OPTIONS+=" -Wall"
OPTIONS+=" -Wswitch"
OPTIONS+=" -Wno-deprecated-declarations"
OPTIONS+=" -Wempty-body"
OPTIONS+=" -Wconversion"
OPTIONS+=" -Wreturn-type"
OPTIONS+=" -Wparentheses"
OPTIONS+=" -Wno-format"
OPTIONS+=" -Wuninitialized"
OPTIONS+=" -Wunreachable-code"
OPTIONS+=" -Wunused-function"
OPTIONS+=" -Wunused-value"
OPTIONS+=" -Wunused-variable"
OPTIONS+=" -Wno-unknown-pragmas"
OPTIONS+=" -Wno-reorder"
OPTIONS+=" -fno-strict-aliasing"
OPTIONS+=" -fthreadsafe-statics"
OPTIONS+=" -fexceptions"
OPTIONS+=" -frtti"

case $CONFIGURATION in
	"Debug"		)OPTIONS+=" -fno-omit-frame-pointer -D _DEBUG -g2 -gdwarf-2 -O0";;
	#"DebugRT"	)OPTIONS+=" -fno-omit-frame-pointer -fpic -D _DEBUG -g2 -gdwarf-2 -O0";;
	"Release"	)OPTIONS+=" -fomit-frame-pointer -D NDEBUG -g1 -O3";;
	#"ReleaseRT"	)OPTIONS+=" -fomit-frame-pointer -fpic -D NDEBUG -g1 -O3";;
	*			)echo "Invalid configuation '$CONFIGURATION'";exit 1;;
esac

#TODO: need further investigation. -m switch makes programs unlinkable even if both libs and program have it.
case $PLATFORM in
	"x86"	);;#OPTIONS+=" -m32";;
	"x64"	);;#OPTIONS+=" -m64";;
	#"ARM"	)OPTIONS+=" -m32";;
	#"ARM64"	)OPTIONS+=" -m64";;
	*		)echo "Invalid platform '$PLATFORM'";exit 1;;
esac

if [ "$PROJECT" = "Platform" ]
then
	OPTIONS+=" -I /usr/include/freetype2"
fi

NEED_PRECOMPILED_HEADER=0
if [ -f "$WORK_PATH/stdafx.h.gch" ]
then
	DATE=$(date -r "$WORK_PATH/stdafx.h.gch" +"%Y%m%d%H%M%S")
	declare -A HEADER_FILES
	eval $(find "$WORK_PATH/" -name "*.h" -printf "HEADER_FILES[%P]=%TY%Tm%Td%TH%TM%.2TS;")
	MODIFIED_AT='00000000000000';
	for key in ${!HEADER_FILES[@]}
	do
		if (( ${HEADER_FILES[$key]} > $MODIFIED_AT ))
		then
			MODIFIED_AT=${HEADER_FILES[$key]}
		fi
	done
	unset HEADER_FILES
	if (( $DATE < $MODIFIED_AT ))
	then
		NEED_PRECOMPILED_HEADER=1
	fi
else
	NEED_PRECOMPILED_HEADER=1
fi

BUILT_COUNT=0
if (( $NEED_PRECOMPILED_HEADER==1 ))
then
	echo "Compiling $WORK_PATH/stdafx.h"
	g++ -c -x c++-header $WORK_PATH/stdafx.h -o $WORK_PATH/stdafx.h.gch $OPTIONS
	RESULT_CODE=$?
	if [ $RESULT_CODE != 0 ]
	then
		echo "Failed to compile precompiled header. 'g++' has exited with code '$RESULT_CODE'"
		exit $RESULT_CODE
	fi
	((BUILT_COUNT+=1))
fi


declare -A SOURCE_FILES
eval $(find "$WORK_PATH/" -type f \( -name "*.cpp" -or -name "*.c" \) -printf "SOURCE_FILES[%P]=%TY%Tm%Td%TH%TM%.2TS;")
COUNTER=1
for key in ${!SOURCE_FILES[@]}
do
	NEED_BUILD=0
	BASE_NAME=${key%.c}
	BASE_NAME=${BASE_NAME%.cpp}
	
	if (( $NEED_PRECOMPILED_HEADER == 1 ))
	then
		NEED_BUILD=1
	else
		if [ -f "$WORK_PATH/obj/$PLATFORM/$CONFIGURATION/$BASE_NAME.o" ]
		then
			DATE=$(date -r "$WORK_PATH/obj/$PLATFORM/$CONFIGURATION/$BASE_NAME.o" +"%Y%m%d%H%M%S")
			if (( ${SOURCE_FILES[$key]} > $DATE ))
			then
				NEED_BUILD=1
			fi
		else
			NEED_BUILD=1
		fi
	fi
	if (( $NEED_BUILD==1 ))
	then
		DIR_NAME=$(dirname $key)
		if [ ! -d "$WORK_PATH/obj/$PLATFORM/$CONFIGURATION/$DIR_NAME" ]
		then
			mkdir -p "$WORK_PATH/obj/$PLATFORM/$CONFIGURATION/$DIR_NAME"
		fi
		g++ -c -x c++ $WORK_PATH/$key -o $WORK_PATH/obj/$PLATFORM/$CONFIGURATION/$BASE_NAME.o $OPTIONS
		RESULT_CODE=$?
		if [ $RESULT_CODE != 0 ]
		then
			printf "Compiling [%4d/%4d] %s\n" $COUNTER ${#SOURCE_FILES[@]} "$WORK_PATH/$key ... FAILED. 'g++' has exited with code '$RESULT_CODE'"
			exit $RESULT_CODE
		fi
		printf "Compiling [%4d/%4d] %s\n" $COUNTER ${#SOURCE_FILES[@]} "$WORK_PATH/$key ... OK"
		((BUILT_COUNT+=1))
	#else
	#	printf "Compiling [%4d/%4d] %s\n" $COUNTER ${#SOURCE_FILES[@]} "$WORK_PATH/$key ... up to date"
	fi
	((COUNTER+=1))
done

echo "Linking"
NEED_LINKING=0
if (( $BUILT_COUNT > 0 ))
then
	NEED_LINKING=1
else
	if [ ! -f "$PWD/$PLATFORM/$CONFIGURATION/lib${PROJECT}.a" ]
	then
		NEED_LINKING=1
	fi
fi
if (( $NEED_LINKING == 1 ))
then
	DIR_NAME="$PWD/$PLATFORM/$CONFIGURATION"
	if [ ! -d $DIR_NAME ]
	then
		mkdir -p $DIR_NAME
	fi
	#if (( $CONFIGURATION == 'DebugRT' || $CONFIGURATION == 'ReleaseRT' ))
	#then
	#	LIB_FILENAME="$DIR_NAME/lib${PROJECT}.so"
	#	echo "Linking $LIB_FILENAME"
	#	rm -f $LIB_FILENAME
	#	declare -A OBJECT_FILES
	#	eval $(find "$WORK_PATH/obj/$PLATFORM/$CONFIGURATION" -name "*.o" -printf "OBJECT_FILES[%P]=1;")
	#	FILES=""
	#	for key in ${!OBJECT_FILES[@]}
	#	do
	#		FILES+=" $WORK_PATH/obj/$PLATFORM/$CONFIGURATION/$key"
	#	done
	#	$CMD = "g++ -shared -o $LIB_FILENAME $FILES"
	#	if (( $PROJECT != "Nitisa" ))
	#	then
	#		CMD+=" -lNitisa"
	#	fi
	#	if (( $PROJECT != "Standard" && $PROJECT != "Nitisa" ))
	#	then
	#		CMD+=" -lStandard"
	#	fi
	#	RESULT_CODE=$?
	#	if [ $RESULT_CODE != 0 ]
	#	then
	#		echo "Failed. 'g++' has exited with code '$RESULT_CODE'"
	#		exit $RESULT_CODE
	#	fi
	#	if [ $BRANCH == "master" ]
	#	then
	#		cp $LIB_FILENAME /tmp/lib${PROJECT}.so
	#	fi
	#else
		LIB_FILENAME="$DIR_NAME/lib${PROJECT}.a"
		rm -f $LIB_FILENAME
		declare -A OBJECT_FILES
		eval $(find "$WORK_PATH/obj/$PLATFORM/$CONFIGURATION" -name "*.o" -printf "OBJECT_FILES[%P]=1;")
		FILES=""
		for key in ${!OBJECT_FILES[@]}
		do
			if (( ${#FILES} + ${#key} > 64000 ))
			then
				ar -q $LIB_FILENAME $FILES
				RESULT_CODE=$?
				if [ $RESULT_CODE != 0 ]
				then
					echo "Failed. 'ar' has exited with code '$RESULT_CODE'"
					exit $RESULT_CODE
				fi
				FILES="$WORK_PATH/obj/$PLATFORM/$CONFIGURATION/$key"
			else
				FILES+=" $WORK_PATH/obj/$PLATFORM/$CONFIGURATION/$key"
			fi
		done
		ar -q $LIB_FILENAME $FILES
		RESULT_CODE=$?
		if [ $RESULT_CODE != 0 ]
		then
			echo "Failed. 'ar' has exited with code '$RESULT_CODE'"
			exit $RESULT_CODE
		fi
		ar -s $LIB_FILENAME
		if [ $RESULT_CODE != 0 ]
		then
			echo "Failed. 'ar' has exited with code '$RESULT_CODE'"
			exit $RESULT_CODE
		fi
		if [ $BRANCH == "master" ]
		then
			cp $LIB_FILENAME /tmp/lib${PROJECT}.a
		fi
	#fi
fi
echo "FINISHED"