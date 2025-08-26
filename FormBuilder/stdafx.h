// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include <codecvt>
#include <locale>
#include <sstream>

#include "Nitisa/Nitisa.h"
#include "Standard/Standard.h"
#include "Platform/Platform.h"
#include "Ide/Ide.h"
#if defined(VS_INTEGRATION) || defined(USE_DIALOGBOXES)
#include "Platform/Platform.h"
#include "Extended/Extended.h"
#include "OpenGL/OpenGL.h"
#include "Charts/Charts.h"
#endif

#if !defined(VS_INTEGRATION)
#include "resource.h"
#endif

#include "Application/Application.h"
#include "Core/ComponentList.h"
#include "Core/Consts.h"
#include "Core/ControlList.h"
#include "Core/Enums.h"
#include "Core/Types.h"
#include "Core/UpdateChecker.h"
#include "Core/Utils.h"
#include "Editor/Editor.h"
#include "Exporters/BaseExporter.h"
#include "Exporters/ExporterHeaderDialogBox.h"
#include "Exporters/ExporterHeaderForm.h"
#include "Forms/Configuration/DialogBoxConfiguration.h"
#include "Forms/Configuration/FormConfiguration.h"
#include "Forms/Empty/FormEmpty.h"
#include "Forms/Main/FormMain.h"
#include "Forms/Main/FormMainService.h"
#include "Interfaces/IExporter.h"
#include "Interfaces/ILoader.h"
#include "Interfaces/ISaver.h"
#include "Loaders/LoaderDefault.h"
#include "Savers/Saver.h"