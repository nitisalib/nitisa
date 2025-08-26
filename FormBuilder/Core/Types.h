// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Math/RectF.h"
#include "Enums.h"
#include <utility>
#include <vector>

namespace nitisa
{
	class IComponent;
	class IControl;
	class IEventList;
	class IPackageComponent;
	class IPackageControl;
	class IPropertyList;

	namespace fb
	{
		struct EXPORT_SETTINGS
		{
			String Namespace;
			String Prefix;
			String WidgetsSection;
			String DialogBoxPackage;
			String DialogBoxClass;
			bool GenerateGetters;
			ExportAs ExportAs;
			std::vector<std::pair<String, String>> OverwriteIncludes;
			std::vector<std::pair<String, String>> OverwriteNamespaces;

			EXPORT_SETTINGS();
			EXPORT_SETTINGS(const EXPORT_SETTINGS &other) = default;
			EXPORT_SETTINGS(EXPORT_SETTINGS &&other) = default;

			EXPORT_SETTINGS &operator=(const EXPORT_SETTINGS &other) = default;
			EXPORT_SETTINGS &operator=(EXPORT_SETTINGS &&other) = default;
		};

		struct SETTINGS : public EXPORT_SETTINGS
		{
			bool GridX;
			bool GridY;
			bool GridRotate;
			float GridXStep;
			float GridYStep;
			float GridRotateStep;
			float RotateShift;
			float GridPointSize;
			Color GridPointColor;
			float SelectionPointSize;
			float SelectionBorderWidth;
			Color SelectionBorderColor;
			Color SelectionBackgroundColor;
			RectF HighlightBorderWidth;
			BorderColor HighlightBorderColor;
			
			SETTINGS();
			SETTINGS(const SETTINGS &other) = default;
			SETTINGS(SETTINGS &&other) = default;

			SETTINGS &operator=(const SETTINGS &other) = default;
			SETTINGS &operator=(SETTINGS &&other) = default;

			bool Load(const String &filename);
			bool Save(const String &filename);
		};

		struct COMPONENT_INFO
		{
			IComponent *Component;
			IEventList *Events;
			IPropertyList *Properties;
			IPackageComponent *PackageComponent;
			int Index; // Index of package component in Editor
		};

		struct CONTROL_INFO
		{
			IControl *Control;
			IEventList *Events;
			IPropertyList *Properties;
			IPackageControl *PackageControl;
			int Index; // Index of package control in Editor
		};
	}
}