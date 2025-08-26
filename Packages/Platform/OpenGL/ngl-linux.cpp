// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#if defined(__linux__) && !defined(__ANDROID__)
#include "ngl.h"

namespace ngl
{
	bool Loaded{ false };
	bool LoadResult{ false };
	nitisa::Version2 Version;
	static bool ctxErrorOccurred{ false };
	const int VERSION_COUNT{ 19 };
	const int Versions[VERSION_COUNT][2]{
		{ 1, 0 },
		{ 1, 1 },
		{ 1, 2 },
		{ 1, 3 },
		{ 1, 4 },
		{ 1, 5 },
		{ 2, 0 },
		{ 2, 1 },
		{ 3, 0 },
		{ 3, 1 },
		{ 3, 2 },
		{ 3, 3 },
		{ 4, 0 },
		{ 4, 1 },
		{ 4, 2 },
		{ 4, 3 },
		{ 4, 4 },
		{ 4, 5 },
		{ 4, 6 }
	};

	void LoadCommonProcedures(int &total, int &loaded);
	
	static int ctxErrorHandler(Display *dpy, XErrorEvent *ev)
	{
		ctxErrorOccurred = true;
		return 0;
	}

	void *GetProc(const char *name, int &total, int &loaded)
	{
		void *p{ (void*)glXGetProcAddress((const GLubyte*)name) };
		total++;
		if (p)
			loaded++;
	#ifdef _DEBUG
		else
			std::cerr << "    Function \"" << name << "\" was not loaded" << std::endl;
	#endif
		return p;
	}

	void LoadProcedures()
	{
		int total, loaded;
		LoadCommonProcedures(total, loaded);

		// GLX_VERSION_1_3
		total = loaded = 0;
		glXGetFBConfigs = (PFNGLXGETFBCONFIGSPROC)GetProc("glXGetFBConfigs", total, loaded);
		glXChooseFBConfig = (PFNGLXCHOOSEFBCONFIGPROC)GetProc("glXChooseFBConfig", total, loaded);
		glXGetFBConfigAttrib = (PFNGLXGETFBCONFIGATTRIBPROC)GetProc("glXGetFBConfigAttrib", total, loaded);
		glXGetVisualFromFBConfig = (PFNGLXGETVISUALFROMFBCONFIGPROC)GetProc("glXGetVisualFromFBConfig", total, loaded);
		glXCreateWindow = (PFNGLXCREATEWINDOWPROC)GetProc("glXCreateWindow", total, loaded);
		glXDestroyWindow = (PFNGLXDESTROYWINDOWPROC)GetProc("glXDestroyWindow", total, loaded);
		glXCreatePixmap = (PFNGLXCREATEPIXMAPPROC)GetProc("glXCreatePixmap", total, loaded);
		glXDestroyPixmap = (PFNGLXDESTROYPIXMAPPROC)GetProc("glXDestroyPixmap", total, loaded);
		glXCreatePbuffer = (PFNGLXCREATEPBUFFERPROC)GetProc("glXCreatePbuffer", total, loaded);
		glXDestroyPbuffer = (PFNGLXDESTROYPBUFFERPROC)GetProc("glXDestroyPbuffer", total, loaded);
		glXQueryDrawable = (PFNGLXQUERYDRAWABLEPROC)GetProc("glXQueryDrawable", total, loaded);
		glXCreateNewContext = (PFNGLXCREATENEWCONTEXTPROC)GetProc("glXCreateNewContext", total, loaded);
		glXMakeContextCurrent = (PFNGLXMAKECONTEXTCURRENTPROC)GetProc("glXMakeContextCurrent", total, loaded);
		glXGetCurrentReadDrawable = (PFNGLXGETCURRENTREADDRAWABLEPROC)GetProc("glXGetCurrentReadDrawable", total, loaded);
		glXQueryContext = (PFNGLXQUERYCONTEXTPROC)GetProc("glXQueryContext", total, loaded);
		glXSelectEvent = (PFNGLXSELECTEVENTPROC)GetProc("glXSelectEvent", total, loaded);
		glXGetSelectedEvent = (PFNGLXGETSELECTEDEVENTPROC)GetProc("glXGetSelectedEvent", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX 1.3" << std::endl;
	#endif
		// GLX_VERSION_1_4
		//total = loaded = 0;
		//glXGetProcAddress = (PFNGLXGETPROCADDRESSPROC)GetProc("glXGetProcAddress", total, loaded);
	//#ifdef _DEBUG
		//if (loaded != total)
		//	std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX 1.4" << std::endl;
	//#endif
		// GLX_ARB_create_context
		total = loaded = 0;
		glXCreateContextAttribsARB = (PFNGLXCREATECONTEXTATTRIBSARBPROC)GetProc("glXCreateContextAttribsARB", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_ARB_create_context" << std::endl;
	#endif
		// GLX_ARB_get_proc_address
		//total = loaded = 0;
		//glXGetProcAddressARB = (PFNGLXGETPROCADDRESSARBPROC)GetProc("glXGetProcAddressARB", total, loaded);
	//#ifdef _DEBUG
		//if (loaded != total)
		//	std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_ARB_get_proc_address" << std::endl;
	//#endif
		// GLX_AMD_gpu_association
		total = loaded = 0;
		glXGetGPUIDsAMD = (PFNGLXGETGPUIDSAMDPROC)GetProc("glXGetGPUIDsAMD", total, loaded);
		glXGetGPUInfoAMD = (PFNGLXGETGPUINFOAMDPROC)GetProc("glXGetGPUInfoAMD", total, loaded);
		glXGetContextGPUIDAMD = (PFNGLXGETCONTEXTGPUIDAMDPROC)GetProc("glXGetContextGPUIDAMD", total, loaded);
		glXCreateAssociatedContextAMD = (PFNGLXCREATEASSOCIATEDCONTEXTAMDPROC)GetProc("glXCreateAssociatedContextAMD", total, loaded);
		glXCreateAssociatedContextAttribsAMD = (PFNGLXCREATEASSOCIATEDCONTEXTATTRIBSAMDPROC)GetProc("glXCreateAssociatedContextAttribsAMD", total, loaded);
		glXDeleteAssociatedContextAMD = (PFNGLXDELETEASSOCIATEDCONTEXTAMDPROC)GetProc("glXDeleteAssociatedContextAMD", total, loaded);
		glXMakeAssociatedContextCurrentAMD = (PFNGLXMAKEASSOCIATEDCONTEXTCURRENTAMDPROC)GetProc("glXMakeAssociatedContextCurrentAMD", total, loaded);
		glXGetCurrentAssociatedContextAMD = (PFNGLXGETCURRENTASSOCIATEDCONTEXTAMDPROC)GetProc("glXGetCurrentAssociatedContextAMD", total, loaded);
		glXBlitContextFramebufferAMD = (PFNGLXBLITCONTEXTFRAMEBUFFERAMDPROC)GetProc("glXBlitContextFramebufferAMD", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_AMD_gpu_association" << std::endl;
	#endif
		// GLX_EXT_import_context
		total = loaded = 0;
		glXGetCurrentDisplayEXT = (PFNGLXGETCURRENTDISPLAYEXTPROC)GetProc("glXGetCurrentDisplayEXT", total, loaded);
		glXQueryContextInfoEXT = (PFNGLXQUERYCONTEXTINFOEXTPROC)GetProc("glXQueryContextInfoEXT", total, loaded);
		glXGetContextIDEXT = (PFNGLXGETCONTEXTIDEXTPROC)GetProc("glXGetContextIDEXT", total, loaded);
		glXImportContextEXT = (PFNGLXIMPORTCONTEXTEXTPROC)GetProc("glXImportContextEXT", total, loaded);
		glXFreeContextEXT = (PFNGLXFREECONTEXTEXTPROC)GetProc("glXFreeContextEXT", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_EXT_import_context" << std::endl;
	#endif
		// GLX_EXT_swap_control
		total = loaded = 0;
		glXSwapIntervalEXT = (PFNGLXSWAPINTERVALEXTPROC)GetProc("glXSwapIntervalEXT", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_EXT_swap_control" << std::endl;
	#endif
		// GLX_EXT_texture_from_pixmap
		total = loaded = 0;
		glXBindTexImageEXT = (PFNGLXBINDTEXIMAGEEXTPROC)GetProc("glXBindTexImageEXT", total, loaded);
		glXReleaseTexImageEXT = (PFNGLXRELEASETEXIMAGEEXTPROC)GetProc("glXReleaseTexImageEXT", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_EXT_texture_from_pixmap" << std::endl;
	#endif
		// GLX_MESA_agp_offset
		total = loaded = 0;
		glXGetAGPOffsetMESA = (PFNGLXGETAGPOFFSETMESAPROC)GetProc("glXGetAGPOffsetMESA", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_MESA_agp_offset" << std::endl;
	#endif
		// GLX_MESA_copy_sub_buffer
		total = loaded = 0;
		glXCopySubBufferMESA = (PFNGLXCOPYSUBBUFFERMESAPROC)GetProc("glXCopySubBufferMESA", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_MESA_copy_sub_buffer" << std::endl;
	#endif
		// GLX_MESA_pixmap_colormap
		total = loaded = 0;
		glXCreateGLXPixmapMESA = (PFNGLXCREATEGLXPIXMAPMESAPROC)GetProc("glXCreateGLXPixmapMESA", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_MESA_pixmap_colormap" << std::endl;
	#endif
		// GLX_MESA_query_renderer
		total = loaded = 0;
		glXQueryCurrentRendererIntegerMESA = (PFNGLXQUERYCURRENTRENDERERINTEGERMESAPROC)GetProc("glXQueryCurrentRendererIntegerMESA", total, loaded);
		glXQueryCurrentRendererStringMESA = (PFNGLXQUERYCURRENTRENDERERSTRINGMESAPROC)GetProc("glXQueryCurrentRendererStringMESA", total, loaded);
		glXQueryRendererIntegerMESA = (PFNGLXQUERYRENDERERINTEGERMESAPROC)GetProc("glXQueryRendererIntegerMESA", total, loaded);
		glXQueryRendererStringMESA = (PFNGLXQUERYRENDERERSTRINGMESAPROC)GetProc("glXQueryRendererStringMESA", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_MESA_query_renderer" << std::endl;
	#endif
		// GLX_MESA_release_buffers
		total = loaded = 0;
		glXReleaseBuffersMESA = (PFNGLXRELEASEBUFFERSMESAPROC)GetProc("glXReleaseBuffersMESA", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_MESA_release_buffers" << std::endl;
	#endif
		// GLX_MESA_set_3dfx_mode
		total = loaded = 0;
		glXSet3DfxModeMESA = (PFNGLXSET3DFXMODEMESAPROC)GetProc("glXSet3DfxModeMESA", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_MESA_set_3dfx_mode" << std::endl;
	#endif
		// GLX_MESA_swap_control
		total = loaded = 0;
		glXGetSwapIntervalMESA = (PFNGLXGETSWAPINTERVALMESAPROC)GetProc("glXGetSwapIntervalMESA", total, loaded);
		glXSwapIntervalMESA = (PFNGLXSWAPINTERVALMESAPROC)GetProc("glXSwapIntervalMESA", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_MESA_swap_control" << std::endl;
	#endif
		// GLX_NV_copy_buffer
		total = loaded = 0;
		glXCopyBufferSubDataNV = (PFNGLXCOPYBUFFERSUBDATANVPROC)GetProc("glXCopyBufferSubDataNV", total, loaded);
		glXNamedCopyBufferSubDataNV = (PFNGLXNAMEDCOPYBUFFERSUBDATANVPROC)GetProc("glXNamedCopyBufferSubDataNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_NV_copy_buffer" << std::endl;
	#endif
		// GLX_NV_copy_image
		total = loaded = 0;
		glXCopyImageSubDataNV = (PFNGLXCOPYIMAGESUBDATANVPROC)GetProc("glXCopyImageSubDataNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_NV_copy_image" << std::endl;
	#endif
		// GLX_NV_delay_before_swap
		total = loaded = 0;
		glXDelayBeforeSwapNV = (PFNGLXDELAYBEFORESWAPNVPROC)GetProc("glXDelayBeforeSwapNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_NV_delay_before_swap" << std::endl;
	#endif
		// GLX_NV_present_video
		total = loaded = 0;
		glXEnumerateVideoDevicesNV = (PFNGLXENUMERATEVIDEODEVICESNVPROC)GetProc("glXEnumerateVideoDevicesNV", total, loaded);
		glXBindVideoDeviceNV = (PFNGLXBINDVIDEODEVICENVPROC)GetProc("glXBindVideoDeviceNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_NV_present_video" << std::endl;
	#endif
		// GLX_NV_swap_group
		total = loaded = 0;
		glXJoinSwapGroupNV = (PFNGLXJOINSWAPGROUPNVPROC)GetProc("glXJoinSwapGroupNV", total, loaded);
		glXBindSwapBarrierNV = (PFNGLXBINDSWAPBARRIERNVPROC)GetProc("glXBindSwapBarrierNV", total, loaded);
		glXQuerySwapGroupNV = (PFNGLXQUERYSWAPGROUPNVPROC)GetProc("glXQuerySwapGroupNV", total, loaded);
		glXQueryMaxSwapGroupsNV = (PFNGLXQUERYMAXSWAPGROUPSNVPROC)GetProc("glXQueryMaxSwapGroupsNV", total, loaded);
		glXQueryFrameCountNV = (PFNGLXQUERYFRAMECOUNTNVPROC)GetProc("glXQueryFrameCountNV", total, loaded);
		glXResetFrameCountNV = (PFNGLXRESETFRAMECOUNTNVPROC)GetProc("glXResetFrameCountNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_NV_swap_group" << std::endl;
	#endif
		// GLX_NV_video_capture
		total = loaded = 0;
		glXBindVideoCaptureDeviceNV = (PFNGLXBINDVIDEOCAPTUREDEVICENVPROC)GetProc("glXBindVideoCaptureDeviceNV", total, loaded);
		glXEnumerateVideoCaptureDevicesNV = (PFNGLXENUMERATEVIDEOCAPTUREDEVICESNVPROC)GetProc("glXEnumerateVideoCaptureDevicesNV", total, loaded);
		glXLockVideoCaptureDeviceNV = (PFNGLXLOCKVIDEOCAPTUREDEVICENVPROC)GetProc("glXLockVideoCaptureDeviceNV", total, loaded);
		glXQueryVideoCaptureDeviceNV = (PFNGLXQUERYVIDEOCAPTUREDEVICENVPROC)GetProc("glXQueryVideoCaptureDeviceNV", total, loaded);
		glXReleaseVideoCaptureDeviceNV = (PFNGLXRELEASEVIDEOCAPTUREDEVICENVPROC)GetProc("glXReleaseVideoCaptureDeviceNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_NV_video_capture" << std::endl;
	#endif
		// GLX_NV_video_out
		total = loaded = 0;
		glXGetVideoDeviceNV = (PFNGLXGETVIDEODEVICENVPROC)GetProc("glXGetVideoDeviceNV", total, loaded);
		glXReleaseVideoDeviceNV = (PFNGLXRELEASEVIDEODEVICENVPROC)GetProc("glXReleaseVideoDeviceNV", total, loaded);
		glXBindVideoImageNV = (PFNGLXBINDVIDEOIMAGENVPROC)GetProc("glXBindVideoImageNV", total, loaded);
		glXReleaseVideoImageNV = (PFNGLXRELEASEVIDEOIMAGENVPROC)GetProc("glXReleaseVideoImageNV", total, loaded);
		glXSendPbufferToVideoNV = (PFNGLXSENDPBUFFERTOVIDEONVPROC)GetProc("glXSendPbufferToVideoNV", total, loaded);
		glXGetVideoInfoNV = (PFNGLXGETVIDEOINFONVPROC)GetProc("glXGetVideoInfoNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_NV_video_out" << std::endl;
	#endif
		// GLX_OML_sync_control
		total = loaded = 0;
		glXGetSyncValuesOML = (PFNGLXGETSYNCVALUESOMLPROC)GetProc("glXGetSyncValuesOML", total, loaded);
		glXGetMscRateOML = (PFNGLXGETMSCRATEOMLPROC)GetProc("glXGetMscRateOML", total, loaded);
		glXSwapBuffersMscOML = (PFNGLXSWAPBUFFERSMSCOMLPROC)GetProc("glXSwapBuffersMscOML", total, loaded);
		glXWaitForMscOML = (PFNGLXWAITFORMSCOMLPROC)GetProc("glXWaitForMscOML", total, loaded);
		glXWaitForSbcOML = (PFNGLXWAITFORSBCOMLPROC)GetProc("glXWaitForSbcOML", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_OML_sync_control" << std::endl;
	#endif
		// GLX_SGIX_dmbuffer
	#ifdef _DM_BUFFER_H_
		total = loaded = 0;
		glXAssociateDMPbufferSGIX = (PFNGLXASSOCIATEDMPBUFFERSGIXPROC)GetProc("glXAssociateDMPbufferSGIX", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_SGIX_dmbuffer" << std::endl;
	#endif
	#endif
		// GLX_SGIX_fbconfig
		total = loaded = 0;
		glXGetFBConfigAttribSGIX = (PFNGLXGETFBCONFIGATTRIBSGIXPROC)GetProc("glXGetFBConfigAttribSGIX", total, loaded);
		glXChooseFBConfigSGIX = (PFNGLXCHOOSEFBCONFIGSGIXPROC)GetProc("glXChooseFBConfigSGIX", total, loaded);
		glXCreateGLXPixmapWithConfigSGIX = (PFNGLXCREATEGLXPIXMAPWITHCONFIGSGIXPROC)GetProc("glXCreateGLXPixmapWithConfigSGIX", total, loaded);
		glXCreateContextWithConfigSGIX = (PFNGLXCREATECONTEXTWITHCONFIGSGIXPROC)GetProc("glXCreateContextWithConfigSGIX", total, loaded);
		glXGetVisualFromFBConfigSGIX = (PFNGLXGETVISUALFROMFBCONFIGSGIXPROC)GetProc("glXGetVisualFromFBConfigSGIX", total, loaded);
		glXGetFBConfigFromVisualSGIX = (PFNGLXGETFBCONFIGFROMVISUALSGIXPROC)GetProc("glXGetFBConfigFromVisualSGIX", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_SGIX_fbconfig" << std::endl;
	#endif
		// GLX_SGIX_hyperpipe
		total = loaded = 0;
		glXQueryHyperpipeNetworkSGIX = (PFNGLXQUERYHYPERPIPENETWORKSGIXPROC)GetProc("glXQueryHyperpipeNetworkSGIX", total, loaded);
		glXHyperpipeConfigSGIX = (PFNGLXHYPERPIPECONFIGSGIXPROC)GetProc("glXHyperpipeConfigSGIX", total, loaded);
		glXQueryHyperpipeConfigSGIX = (PFNGLXQUERYHYPERPIPECONFIGSGIXPROC)GetProc("glXQueryHyperpipeConfigSGIX", total, loaded);
		glXDestroyHyperpipeConfigSGIX = (PFNGLXDESTROYHYPERPIPECONFIGSGIXPROC)GetProc("glXDestroyHyperpipeConfigSGIX", total, loaded);
		glXBindHyperpipeSGIX = (PFNGLXBINDHYPERPIPESGIXPROC)GetProc("glXBindHyperpipeSGIX", total, loaded);
		glXQueryHyperpipeBestAttribSGIX = (PFNGLXQUERYHYPERPIPEBESTATTRIBSGIXPROC)GetProc("glXQueryHyperpipeBestAttribSGIX", total, loaded);
		glXHyperpipeAttribSGIX = (PFNGLXHYPERPIPEATTRIBSGIXPROC)GetProc("glXHyperpipeAttribSGIX", total, loaded);
		glXQueryHyperpipeAttribSGIX = (PFNGLXQUERYHYPERPIPEATTRIBSGIXPROC)GetProc("glXQueryHyperpipeAttribSGIX", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_SGIX_hyperpipe" << std::endl;
	#endif
		// GLX_SGIX_pbuffer
		total = loaded = 0;
		glXCreateGLXPbufferSGIX = (PFNGLXCREATEGLXPBUFFERSGIXPROC)GetProc("glXCreateGLXPbufferSGIX", total, loaded);
		glXDestroyGLXPbufferSGIX = (PFNGLXDESTROYGLXPBUFFERSGIXPROC)GetProc("glXDestroyGLXPbufferSGIX", total, loaded);
		glXQueryGLXPbufferSGIX = (PFNGLXQUERYGLXPBUFFERSGIXPROC)GetProc("glXQueryGLXPbufferSGIX", total, loaded);
		glXSelectEventSGIX = (PFNGLXSELECTEVENTSGIXPROC)GetProc("glXSelectEventSGIX", total, loaded);
		glXGetSelectedEventSGIX = (PFNGLXGETSELECTEDEVENTSGIXPROC)GetProc("glXGetSelectedEventSGIX", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_SGIX_pbuffer" << std::endl;
	#endif
		// GLX_SGIX_swap_barrier
		total = loaded = 0;
		glXBindSwapBarrierSGIX = (PFNGLXBINDSWAPBARRIERSGIXPROC)GetProc("glXBindSwapBarrierSGIX", total, loaded);
		glXQueryMaxSwapBarriersSGIX = (PFNGLXQUERYMAXSWAPBARRIERSSGIXPROC)GetProc("glXQueryMaxSwapBarriersSGIX", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_SGIX_swap_barrier" << std::endl;
	#endif
		// GLX_SGIX_swap_group
		total = loaded = 0;
		glXJoinSwapGroupSGIX = (PFNGLXJOINSWAPGROUPSGIXPROC)GetProc("glXJoinSwapGroupSGIX", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_SGIX_swap_group" << std::endl;
	#endif
		// GLX_SGIX_video_resize
		total = loaded = 0;
		glXBindChannelToWindowSGIX = (PFNGLXBINDCHANNELTOWINDOWSGIXPROC)GetProc("glXBindChannelToWindowSGIX", total, loaded);
		glXChannelRectSGIX = (PFNGLXCHANNELRECTSGIXPROC)GetProc("glXChannelRectSGIX", total, loaded);
		glXQueryChannelRectSGIX = (PFNGLXQUERYCHANNELRECTSGIXPROC)GetProc("glXQueryChannelRectSGIX", total, loaded);
		glXQueryChannelDeltasSGIX = (PFNGLXQUERYCHANNELDELTASSGIXPROC)GetProc("glXQueryChannelDeltasSGIX", total, loaded);
		glXChannelRectSyncSGIX = (PFNGLXCHANNELRECTSYNCSGIXPROC)GetProc("glXChannelRectSyncSGIX", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_SGIX_video_resize" << std::endl;
	#endif
		// GLX_SGIX_video_source
	#ifdef _VL_H
		total = loaded = 0;
		glXCreateGLXVideoSourceSGIX = (PFNGLXCREATEGLXVIDEOSOURCESGIXPROC)GetProc("glXCreateGLXVideoSourceSGIX", total, loaded);
		glXDestroyGLXVideoSourceSGIX = (PFNGLXDESTROYGLXVIDEOSOURCESGIXPROC)GetProc("glXDestroyGLXVideoSourceSGIX", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_SGIX_video_source" << std::endl;
	#endif
	#endif
		// GLX_SGI_cushion
		total = loaded = 0;
		glXCushionSGI = (PFNGLXCUSHIONSGIPROC)GetProc("glXCushionSGI", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_SGI_cushion" << std::endl;
	#endif
		// GLX_SGI_make_current_read
		total = loaded = 0;
		glXMakeCurrentReadSGI = (PFNGLXMAKECURRENTREADSGIPROC)GetProc("glXMakeCurrentReadSGI", total, loaded);
		glXGetCurrentReadDrawableSGI = (PFNGLXGETCURRENTREADDRAWABLESGIPROC)GetProc("glXGetCurrentReadDrawableSGI", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_SGI_make_current_read" << std::endl;
	#endif
		// GLX_SGI_swap_control
		total = loaded = 0;
		glXSwapIntervalSGI = (PFNGLXSWAPINTERVALSGIPROC)GetProc("glXSwapIntervalSGI", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_SGI_swap_control" << std::endl;
	#endif
		// GLX_SGI_video_sync
		total = loaded = 0;
		glXGetVideoSyncSGI = (PFNGLXGETVIDEOSYNCSGIPROC)GetProc("glXGetVideoSyncSGI", total, loaded);
		glXWaitVideoSyncSGI = (PFNGLXWAITVIDEOSYNCSGIPROC)GetProc("glXWaitVideoSyncSGI", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_SGI_video_sync" << std::endl;
	#endif
		// GLX_SUN_get_transparent_index
		total = loaded = 0;
		glXGetTransparentIndexSUN = (PFNGLXGETTRANSPARENTINDEXSUNPROC)GetProc("glXGetTransparentIndexSUN", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GLX_SUN_get_transparent_index" << std::endl;
	#endif
	}

	bool load(nitisa::Version2 *version, PlatformData *pd)
	{
		if (!Loaded)
		{
			Loaded = true;
			Display *display{ (pd && pd->display) ? pd->display : XOpenDisplay(nullptr) };
			if (!display)
				return false;
			Window window{ (pd && pd->window) ? pd->window : XCreateSimpleWindow(display, RootWindow(display, DefaultScreen(display)), 0, 0, 640, 480, 0, None, None) };
			if (!window)
			{
				if (!pd || !pd->display)
					XCloseDisplay(display);
				return false;
			}
			LoadProcedures();
			if (glGetIntegerv && glXCreateContextAttribsARB)
			{
				int visual_attributes[]{
					GLX_X_RENDERABLE, True,
					GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
					GLX_RENDER_TYPE, GLX_RGBA_BIT,
					GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
					GLX_RED_SIZE, 8,
					GLX_GREEN_SIZE, 8,
					GLX_BLUE_SIZE, 8,
					GLX_ALPHA_SIZE, 8,
					GLX_DEPTH_SIZE, 24,
					GLX_STENCIL_SIZE, 8,
					GLX_DOUBLEBUFFER, False,
					None
				};
				int fb_config_count;
				GLXFBConfig config{ nullptr };
				GLXFBConfig *fb_configs{ glXChooseFBConfig(display, DefaultScreen(display), visual_attributes, &fb_config_count) };
				if (fb_configs)
				{
					if (fb_config_count > 0)
						config = fb_configs[0];
					XFree(fb_configs);
					if (fb_config_count > 0)
					{
						ctxErrorOccurred = false;
						int(*oldHandler)(Display*, XErrorEvent*) { XSetErrorHandler(&ctxErrorHandler) };
						GLXContext ctx{ nullptr };
						nitisa::Version2 v;
						for (int i = VERSION_COUNT - 1; i >= 0; i--)
						{
							v.Major = Versions[i][0];
							v.Minor = Versions[i][1];
							const int context_attributes[]{
								GLX_CONTEXT_MAJOR_VERSION_ARB, Versions[i][0],
								GLX_CONTEXT_MINOR_VERSION_ARB, Versions[i][1],
								GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
								None // End of attributes list
							};
							if ((ctx = glXCreateContextAttribsARB(display, config, 0, True, context_attributes)))
								break;
						}
						XSetErrorHandler(oldHandler);
						if (ctx)
						{
							glXDestroyContext(display, ctx);
							Version = v;
							LoadResult = true;
						}
					}
				}
			}
			if (!pd || !pd->window)
				XDestroyWindow(display, window);
			if (!pd || !pd->display)
				XCloseDisplay(display);
		}
		if (version)
			*version = Version;
		return LoadResult;
	}

	bool loaded(nitisa::Version2 *version)
	{
		if (version)
			*version = Version;
		return LoadResult;
	}

	void unload()
	{
		Loaded = LoadResult = false;
		Version = nitisa::Version2{ 0, 0 };
	}
}
#endif