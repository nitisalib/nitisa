// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

// Controls
#include "Controls/BarChart/BarChart.h"
#include "Controls/DoughnutChart/DoughnutChart.h"
#include "Controls/ForexChart/ForexChart.h"
#include "Controls/ForexChart/ForexChartService.h"
#include "Controls/LineChart/LineChart.h"
#include "Controls/MultiBarChart/MultiBarChart.h"
#include "Controls/PieChart/PieChart.h"
#include "Controls/PolarAreaChart/PolarAreaChart.h"
#include "Controls/PolarAreaChart/PolarAreaChartService.h"
#include "Controls/RadarChart/RadarChart.h"
#include "Controls/RadarChart/RadarChartService.h"
#include "Controls/SemiDoughnutChart/SemiDoughnutChart.h"
#include "Controls/SemiPieChart/SemiPieChart.h"
#include "Controls/SplineChart/SplineChart.h"
#include "Controls/StackedBarChart/StackedBarChart.h"
#include "Controls/SteppedLineChart/SteppedLineChart.h"
#include "Controls/IBarChart.h"
#include "Controls/IDoughnutChart.h"
#include "Controls/IForexChart.h"
#include "Controls/ILineChart.h"
#include "Controls/IMultiBarChart.h"
#include "Controls/IPieChart.h"
#include "Controls/IPolarAreaChart.h"
#include "Controls/IRadarChart.h"
#include "Controls/ISemiDoughnutChart.h"
#include "Controls/ISemiPieChart.h"
#include "Controls/ISplineChart.h"
#include "Controls/IStackedBarChart.h"
#include "Controls/ISteppedLineChart.h"

// Core
#include "Core/BarChartRenderer.h"
#include "Core/BezierChartRenderer.h"
#include "Core/ChartData.h"
#include "Core/ChartDataSet.h"
#include "Core/CustomCartesianChart.h"
#include "Core/CustomCartesianChartEventList.h"
#include "Core/CustomCartesianChartPropertyList.h"
#include "Core/CustomCartesianChartService.h"
#include "Core/CustomRadialChart.h"
#include "Core/CustomRadialChartEventList.h"
#include "Core/CustomRadialChartPropertyList.h"
#include "Core/CustomRadialChartService.h"
#include "Core/Enums.h"
#include "Core/LineChartRenderer.h"
#include "Core/SteppedLineChartRenderer.h"
#include "Core/Utils.h"

// Forms
#include "Forms/ChartDataSet/DialogBoxChartDataSet.h"
#include "Forms/ChartDataSet/FormChartDataSet.h"
#include "Forms/ForexChartData/DialogBoxForexChartData.h"
#include "Forms/ForexChartData/FormForexChartData.h"
#include "Forms/LineInterpolationPositionArray/DialogBoxLineInterpolationPositionArray.h"
#include "Forms/LineInterpolationPositionArray/FormLineInterpolationPositionArray.h"
#include "Forms/IFormChartDataSet.h"
#include "Forms/IFormForexChartData.h"
#include "Forms/IFormLineInterpolationPositionArray.h"

// Interfaces
#include "Interfaces/ICartesianChart.h"
#include "Interfaces/IChartData.h"
#include "Interfaces/IChartDataSet.h"
#include "Interfaces/IChartRenderer.h"
#include "Interfaces/IRadialChart.h"
#include "Interfaces/IUpdateListener.h"

// Package controls
#include "Package/Controls/BarChart/BarChartEventList.h"
#include "Package/Controls/BarChart/BarChartPropertyList.h"
#include "Package/Controls/BarChart/PackageBarChart.h"
#include "Package/Controls/DoughnutChart/DoughnutChartEventList.h"
#include "Package/Controls/DoughnutChart/DoughnutChartPropertyList.h"
#include "Package/Controls/DoughnutChart/PackageDoughnutChart.h"
#include "Package/Controls/ForexChart/ForexChartEventList.h"
#include "Package/Controls/ForexChart/ForexChartPropertyList.h"
#include "Package/Controls/ForexChart/PackageForexChart.h"
#include "Package/Controls/LineChart/LineChartEventList.h"
#include "Package/Controls/LineChart/LineChartPropertyList.h"
#include "Package/Controls/LineChart/PackageLineChart.h"
#include "Package/Controls/MultiBarChart/MultiBarChartEventList.h"
#include "Package/Controls/MultiBarChart/MultiBarChartPropertyList.h"
#include "Package/Controls/MultiBarChart/PackageMultiBarChart.h"
#include "Package/Controls/PieChart/PieChartEventList.h"
#include "Package/Controls/PieChart/PieChartPropertyList.h"
#include "Package/Controls/PieChart/PackagePieChart.h"
#include "Package/Controls/PolarAreaChart/PolarAreaChartEventList.h"
#include "Package/Controls/PolarAreaChart/PolarAreaChartPropertyList.h"
#include "Package/Controls/PolarAreaChart/PackagePolarAreaChart.h"
#include "Package/Controls/RadarChart/RadarChartEventList.h"
#include "Package/Controls/RadarChart/RadarChartPropertyList.h"
#include "Package/Controls/RadarChart/PackageRadarChart.h"
#include "Package/Controls/SemiDoughnutChart/SemiDoughnutChartEventList.h"
#include "Package/Controls/SemiDoughnutChart/SemiDoughnutChartPropertyList.h"
#include "Package/Controls/SemiDoughnutChart/PackageSemiDoughnutChart.h"
#include "Package/Controls/SemiPieChart/SemiPieChartEventList.h"
#include "Package/Controls/SemiPieChart/SemiPieChartPropertyList.h"
#include "Package/Controls/SemiPieChart/PackageSemiPieChart.h"
#include "Package/Controls/SplineChart/SplineChartEventList.h"
#include "Package/Controls/SplineChart/SplineChartPropertyList.h"
#include "Package/Controls/SplineChart/PackageSplineChart.h"
#include "Package/Controls/StackedBarChart/StackedBarChartEventList.h"
#include "Package/Controls/StackedBarChart/StackedBarChartPropertyList.h"
#include "Package/Controls/StackedBarChart/PackageStackedBarChart.h"
#include "Package/Controls/SteppedLineChart/SteppedLineChartEventList.h"
#include "Package/Controls/SteppedLineChart/SteppedLineChartPropertyList.h"
#include "Package/Controls/SteppedLineChart/PackageSteppedLineChart.h"

// Package core
#include "Package/Core/Consts.h"

// Package forms
#include "Package/Forms/ChartDataSet/FormChartDataSetEventList.h"
#include "Package/Forms/ChartDataSet/FormChartDataSetPropertyList.h"
#include "Package/Forms/ChartDataSet/PackageFormChartDataSet.h"
#include "Package/Forms/ForexChartData/FormForexChartDataEventList.h"
#include "Package/Forms/ForexChartData/FormForexChartDataPropertyList.h"
#include "Package/Forms/ForexChartData/PackageFormForexChartData.h"
#include "Package/Forms/LineInterpolationPositionArray/FormLineInterpolationPositionArrayEventList.h"
#include "Package/Forms/LineInterpolationPositionArray/FormLineInterpolationPositionArrayPropertyList.h"
#include "Package/Forms/LineInterpolationPositionArray/PackageFormLineInterpolationPositionArray.h"

// Package interfaces
#include "Package/Interfaces/IPropertyChartDataSet.h"
#include "Package/Interfaces/IPropertyForexChartData.h"
#include "Package/Interfaces/IPropertyLineInterpolationPositionArray.h"

// Package properties
#include "Package/Properties/PropertyChartDataSet.h"
#include "Package/Properties/PropertyForexChartData.h"
#include "Package/Properties/PropertyLineInterpolationPositionArray.h"

// Package property handlers
#include "Package/PropertyHandlers/ChartDataSet/PropertyHandlerChartDataSet.h"
#include "Package/PropertyHandlers/ForexChartData/PropertyHandlerForexChartData.h"
#include "Package/PropertyHandlers/LineInterpolationPositionArray/PropertyHandlerLineInterpolationPositionArray.h"

// Package
#include "Package/PackageCharts.h"
#include "Package/PackageChartsService.h"