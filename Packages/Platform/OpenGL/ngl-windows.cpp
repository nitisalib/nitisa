// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef _WIN32
#include "ngl.h"

namespace ngl
{
	bool Loaded{ false };
	bool LoadResult{ false };
	nitisa::Version2 Version;
	HMODULE Module{ nullptr };

	void LoadCommonProcedures(int &total, int &loaded);

	void *GetProc(const char *name, int &total, int &loaded)
	{
		void *p{ (void*)wglGetProcAddress(name) };
		if (p == 0 || (p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) || (p == (void*)-1))
			p = (void*)GetProcAddress(Module, name);
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

		// WGL_ARB_buffer_region
		total = loaded = 0;
		wglCreateBufferRegionARB = (PFNWGLCREATEBUFFERREGIONARBPROC)GetProc("wglCreateBufferRegionARB", total, loaded);
		wglDeleteBufferRegionARB = (PFNWGLDELETEBUFFERREGIONARBPROC)GetProc("wglDeleteBufferRegionARB", total, loaded);
		wglSaveBufferRegionARB = (PFNWGLSAVEBUFFERREGIONARBPROC)GetProc("wglSaveBufferRegionARB", total, loaded);
		wglRestoreBufferRegionARB = (PFNWGLRESTOREBUFFERREGIONARBPROC)GetProc("wglRestoreBufferRegionARB", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_ARB_buffer_region" << std::endl;
	#endif
		// WGL_ARB_create_context
		total = loaded = 0;
		wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)GetProc("wglCreateContextAttribsARB", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_ARB_create_context" << std::endl;
	#endif
		// WGL_ARB_extensions_string
		total = loaded = 0;
		wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)GetProc("wglGetExtensionsStringARB", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_ARB_extensions_string" << std::endl;
	#endif
		// WGL_ARB_make_current_read
		total = loaded = 0;
		wglMakeContextCurrentARB = (PFNWGLMAKECONTEXTCURRENTARBPROC)GetProc("wglMakeContextCurrentARB", total, loaded);
		wglGetCurrentReadDCARB = (PFNWGLGETCURRENTREADDCARBPROC)GetProc("wglGetCurrentReadDCARB", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_ARB_make_current_read" << std::endl;
	#endif
		// WGL_ARB_pbuffer
		total = loaded = 0;
		wglCreatePbufferARB = (PFNWGLCREATEPBUFFERARBPROC)GetProc("wglCreatePbufferARB", total, loaded);
		wglGetPbufferDCARB = (PFNWGLGETPBUFFERDCARBPROC)GetProc("wglGetPbufferDCARB", total, loaded);
		wglReleasePbufferDCARB = (PFNWGLRELEASEPBUFFERDCARBPROC)GetProc("wglReleasePbufferDCARB", total, loaded);
		wglDestroyPbufferARB = (PFNWGLDESTROYPBUFFERARBPROC)GetProc("wglDestroyPbufferARB", total, loaded);
		wglQueryPbufferARB = (PFNWGLQUERYPBUFFERARBPROC)GetProc("wglQueryPbufferARB", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_ARB_pbuffer" << std::endl;
	#endif
		// WGL_ARB_pixel_format
		total = loaded = 0;
		wglGetPixelFormatAttribivARB = (PFNWGLGETPIXELFORMATATTRIBIVARBPROC)GetProc("wglGetPixelFormatAttribivARB", total, loaded);
		wglGetPixelFormatAttribfvARB = (PFNWGLGETPIXELFORMATATTRIBFVARBPROC)GetProc("wglGetPixelFormatAttribfvARB", total, loaded);
		wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)GetProc("wglChoosePixelFormatARB", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_ARB_pixel_format" << std::endl;
	#endif
		// WGL_ARB_render_texture
		total = loaded = 0;
		wglBindTexImageARB = (PFNWGLBINDTEXIMAGEARBPROC)GetProc("wglBindTexImageARB", total, loaded);
		wglReleaseTexImageARB = (PFNWGLRELEASETEXIMAGEARBPROC)GetProc("wglReleaseTexImageARB", total, loaded);
		wglSetPbufferAttribARB = (PFNWGLSETPBUFFERATTRIBARBPROC)GetProc("wglSetPbufferAttribARB", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_ARB_render_texture" << std::endl;
	#endif
		// WGL_3DL_stereo_control
		total = loaded = 0;
		wglSetStereoEmitterState3DL = (PFNWGLSETSTEREOEMITTERSTATE3DLPROC)GetProc("wglSetStereoEmitterState3DL", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_3DL_stereo_control" << std::endl;
	#endif
		// WGL_AMD_gpu_association
		total = loaded = 0;
		wglGetGPUIDsAMD = (PFNWGLGETGPUIDSAMDPROC)GetProc("wglGetGPUIDsAMD", total, loaded);
		wglGetGPUInfoAMD = (PFNWGLGETGPUINFOAMDPROC)GetProc("wglGetGPUInfoAMD", total, loaded);
		wglGetContextGPUIDAMD = (PFNWGLGETCONTEXTGPUIDAMDPROC)GetProc("wglGetContextGPUIDAMD", total, loaded);
		wglCreateAssociatedContextAMD = (PFNWGLCREATEASSOCIATEDCONTEXTAMDPROC)GetProc("wglCreateAssociatedContextAMD", total, loaded);
		wglCreateAssociatedContextAttribsAMD = (PFNWGLCREATEASSOCIATEDCONTEXTATTRIBSAMDPROC)GetProc("wglCreateAssociatedContextAttribsAMD", total, loaded);
		wglDeleteAssociatedContextAMD = (PFNWGLDELETEASSOCIATEDCONTEXTAMDPROC)GetProc("wglDeleteAssociatedContextAMD", total, loaded);
		wglMakeAssociatedContextCurrentAMD = (PFNWGLMAKEASSOCIATEDCONTEXTCURRENTAMDPROC)GetProc("wglMakeAssociatedContextCurrentAMD", total, loaded);
		wglGetCurrentAssociatedContextAMD = (PFNWGLGETCURRENTASSOCIATEDCONTEXTAMDPROC)GetProc("wglGetCurrentAssociatedContextAMD", total, loaded);
		wglBlitContextFramebufferAMD = (PFNWGLBLITCONTEXTFRAMEBUFFERAMDPROC)GetProc("wglBlitContextFramebufferAMD", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_AMD_gpu_association" << std::endl;
	#endif
		// WGL_EXT_display_color_table
		total = loaded = 0;
		wglCreateDisplayColorTableEXT = (PFNWGLCREATEDISPLAYCOLORTABLEEXTPROC)GetProc("wglCreateDisplayColorTableEXT", total, loaded);
		wglLoadDisplayColorTableEXT = (PFNWGLLOADDISPLAYCOLORTABLEEXTPROC)GetProc("wglLoadDisplayColorTableEXT", total, loaded);
		wglBindDisplayColorTableEXT = (PFNWGLBINDDISPLAYCOLORTABLEEXTPROC)GetProc("wglBindDisplayColorTableEXT", total, loaded);
		wglDestroyDisplayColorTableEXT = (PFNWGLDESTROYDISPLAYCOLORTABLEEXTPROC)GetProc("wglDestroyDisplayColorTableEXT", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_EXT_display_color_table" << std::endl;
	#endif
		// WGL_EXT_extensions_string
		total = loaded = 0;
		wglGetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC)GetProc("wglGetExtensionsStringEXT", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_EXT_extensions_string" << std::endl;
	#endif
		// WGL_EXT_make_current_read
		total = loaded = 0;
		wglMakeContextCurrentEXT = (PFNWGLMAKECONTEXTCURRENTEXTPROC)GetProc("wglMakeContextCurrentEXT", total, loaded);
		wglGetCurrentReadDCEXT = (PFNWGLGETCURRENTREADDCEXTPROC)GetProc("wglGetCurrentReadDCEXT", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_EXT_make_current_read" << std::endl;
	#endif
		// WGL_EXT_pbuffer
		total = loaded = 0;
		wglCreatePbufferEXT = (PFNWGLCREATEPBUFFEREXTPROC)GetProc("wglCreatePbufferEXT", total, loaded);
		wglGetPbufferDCEXT = (PFNWGLGETPBUFFERDCEXTPROC)GetProc("wglGetPbufferDCEXT", total, loaded);
		wglReleasePbufferDCEXT = (PFNWGLRELEASEPBUFFERDCEXTPROC)GetProc("wglReleasePbufferDCEXT", total, loaded);
		wglDestroyPbufferEXT = (PFNWGLDESTROYPBUFFEREXTPROC)GetProc("wglDestroyPbufferEXT", total, loaded);
		wglQueryPbufferEXT = (PFNWGLQUERYPBUFFEREXTPROC)GetProc("wglQueryPbufferEXT", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_EXT_pbuffer" << std::endl;
	#endif
		// WGL_EXT_pixel_format
		total = loaded = 0;
		wglGetPixelFormatAttribivEXT = (PFNWGLGETPIXELFORMATATTRIBIVEXTPROC)GetProc("wglGetPixelFormatAttribivEXT", total, loaded);
		wglGetPixelFormatAttribfvEXT = (PFNWGLGETPIXELFORMATATTRIBFVEXTPROC)GetProc("wglGetPixelFormatAttribfvEXT", total, loaded);
		wglChoosePixelFormatEXT = (PFNWGLCHOOSEPIXELFORMATEXTPROC)GetProc("wglChoosePixelFormatEXT", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_EXT_pixel_format" << std::endl;
	#endif
		// WGL_EXT_swap_control
		total = loaded = 0;
		wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)GetProc("wglSwapIntervalEXT", total, loaded);
		wglGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC)GetProc("wglGetSwapIntervalEXT", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_EXT_swap_control" << std::endl;
	#endif
		// WGL_I3D_digital_video_control
		total = loaded = 0;
		wglGetDigitalVideoParametersI3D = (PFNWGLGETDIGITALVIDEOPARAMETERSI3DPROC)GetProc("wglGetDigitalVideoParametersI3D", total, loaded);
		wglSetDigitalVideoParametersI3D = (PFNWGLSETDIGITALVIDEOPARAMETERSI3DPROC)GetProc("wglSetDigitalVideoParametersI3D", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_I3D_digital_video_control" << std::endl;
	#endif
		// WGL_I3D_gamma
		total = loaded = 0;
		wglGetGammaTableParametersI3D = (PFNWGLGETGAMMATABLEPARAMETERSI3DPROC)GetProc("wglGetGammaTableParametersI3D", total, loaded);
		wglSetGammaTableParametersI3D = (PFNWGLSETGAMMATABLEPARAMETERSI3DPROC)GetProc("wglSetGammaTableParametersI3D", total, loaded);
		wglGetGammaTableI3D = (PFNWGLGETGAMMATABLEI3DPROC)GetProc("wglGetGammaTableI3D", total, loaded);
		wglSetGammaTableI3D = (PFNWGLSETGAMMATABLEI3DPROC)GetProc("wglSetGammaTableI3D", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_I3D_gamma" << std::endl;
	#endif
		// WGL_I3D_genlock
		total = loaded = 0;
		wglEnableGenlockI3D = (PFNWGLENABLEGENLOCKI3DPROC)GetProc("wglEnableGenlockI3D", total, loaded);
		wglDisableGenlockI3D = (PFNWGLDISABLEGENLOCKI3DPROC)GetProc("wglDisableGenlockI3D", total, loaded);
		wglIsEnabledGenlockI3D = (PFNWGLISENABLEDGENLOCKI3DPROC)GetProc("wglIsEnabledGenlockI3D", total, loaded);
		wglGenlockSourceI3D = (PFNWGLGENLOCKSOURCEI3DPROC)GetProc("wglGenlockSourceI3D", total, loaded);
		wglGetGenlockSourceI3D = (PFNWGLGETGENLOCKSOURCEI3DPROC)GetProc("wglGetGenlockSourceI3D", total, loaded);
		wglGenlockSourceEdgeI3D = (PFNWGLGENLOCKSOURCEEDGEI3DPROC)GetProc("wglGenlockSourceEdgeI3D", total, loaded);
		wglGetGenlockSourceEdgeI3D = (PFNWGLGETGENLOCKSOURCEEDGEI3DPROC)GetProc("wglGetGenlockSourceEdgeI3D", total, loaded);
		wglGenlockSampleRateI3D = (PFNWGLGENLOCKSAMPLERATEI3DPROC)GetProc("wglGenlockSampleRateI3D", total, loaded);
		wglGetGenlockSampleRateI3D = (PFNWGLGETGENLOCKSAMPLERATEI3DPROC)GetProc("wglGetGenlockSampleRateI3D", total, loaded);
		wglGenlockSourceDelayI3D = (PFNWGLGENLOCKSOURCEDELAYI3DPROC)GetProc("wglGenlockSourceDelayI3D", total, loaded);
		wglGetGenlockSourceDelayI3D = (PFNWGLGETGENLOCKSOURCEDELAYI3DPROC)GetProc("wglGetGenlockSourceDelayI3D", total, loaded);
		wglQueryGenlockMaxSourceDelayI3D = (PFNWGLQUERYGENLOCKMAXSOURCEDELAYI3DPROC)GetProc("wglQueryGenlockMaxSourceDelayI3D", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_I3D_genlock" << std::endl;
	#endif
		// WGL_I3D_image_buffer
		total = loaded = 0;
		wglCreateImageBufferI3D = (PFNWGLCREATEIMAGEBUFFERI3DPROC)GetProc("wglCreateImageBufferI3D", total, loaded);
		wglDestroyImageBufferI3D = (PFNWGLDESTROYIMAGEBUFFERI3DPROC)GetProc("wglDestroyImageBufferI3D", total, loaded);
		wglAssociateImageBufferEventsI3D = (PFNWGLASSOCIATEIMAGEBUFFEREVENTSI3DPROC)GetProc("wglAssociateImageBufferEventsI3D", total, loaded);
		wglReleaseImageBufferEventsI3D = (PFNWGLRELEASEIMAGEBUFFEREVENTSI3DPROC)GetProc("wglReleaseImageBufferEventsI3D", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_I3D_image_buffer" << std::endl;
	#endif
		// WGL_I3D_swap_frame_lock
		total = loaded = 0;
		wglEnableFrameLockI3D = (PFNWGLENABLEFRAMELOCKI3DPROC)GetProc("wglEnableFrameLockI3D", total, loaded);
		wglDisableFrameLockI3D = (PFNWGLDISABLEFRAMELOCKI3DPROC)GetProc("wglDisableFrameLockI3D", total, loaded);
		wglIsEnabledFrameLockI3D = (PFNWGLISENABLEDFRAMELOCKI3DPROC)GetProc("wglIsEnabledFrameLockI3D", total, loaded);
		wglQueryFrameLockMasterI3D = (PFNWGLQUERYFRAMELOCKMASTERI3DPROC)GetProc("wglQueryFrameLockMasterI3D", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_I3D_swap_frame_lock" << std::endl;
	#endif
		// WGL_I3D_swap_frame_usage
		total = loaded = 0;
		wglGetFrameUsageI3D = (PFNWGLGETFRAMEUSAGEI3DPROC)GetProc("wglGetFrameUsageI3D", total, loaded);
		wglBeginFrameTrackingI3D = (PFNWGLBEGINFRAMETRACKINGI3DPROC)GetProc("wglBeginFrameTrackingI3D", total, loaded);
		wglEndFrameTrackingI3D = (PFNWGLENDFRAMETRACKINGI3DPROC)GetProc("wglEndFrameTrackingI3D", total, loaded);
		wglQueryFrameTrackingI3D = (PFNWGLQUERYFRAMETRACKINGI3DPROC)GetProc("wglQueryFrameTrackingI3D", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_I3D_swap_frame_usage" << std::endl;
	#endif
		// WGL_NV_DX_interop
		total = loaded = 0;
		wglDXSetResourceShareHandleNV = (PFNWGLDXSETRESOURCESHAREHANDLENVPROC)GetProc("wglDXSetResourceShareHandleNV", total, loaded);
		wglDXOpenDeviceNV = (PFNWGLDXOPENDEVICENVPROC)GetProc("wglDXOpenDeviceNV", total, loaded);
		wglDXCloseDeviceNV = (PFNWGLDXCLOSEDEVICENVPROC)GetProc("wglDXCloseDeviceNV", total, loaded);
		wglDXRegisterObjectNV = (PFNWGLDXREGISTEROBJECTNVPROC)GetProc("wglDXRegisterObjectNV", total, loaded);
		wglDXUnregisterObjectNV = (PFNWGLDXUNREGISTEROBJECTNVPROC)GetProc("wglDXUnregisterObjectNV", total, loaded);
		wglDXObjectAccessNV = (PFNWGLDXOBJECTACCESSNVPROC)GetProc("wglDXObjectAccessNV", total, loaded);
		wglDXLockObjectsNV = (PFNWGLDXLOCKOBJECTSNVPROC)GetProc("wglDXLockObjectsNV", total, loaded);
		wglDXUnlockObjectsNV = (PFNWGLDXUNLOCKOBJECTSNVPROC)GetProc("wglDXUnlockObjectsNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_NV_DX_interop" << std::endl;
	#endif
		// WGL_NV_copy_image
		total = loaded = 0;
		wglCopyImageSubDataNV = (PFNWGLCOPYIMAGESUBDATANVPROC)GetProc("wglCopyImageSubDataNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_NV_copy_image" << std::endl;
	#endif
		// WGL_NV_delay_before_swap
		total = loaded = 0;
		wglDelayBeforeSwapNV = (PFNWGLDELAYBEFORESWAPNVPROC)GetProc("wglDelayBeforeSwapNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_NV_delay_before_swap" << std::endl;
	#endif
		// WGL_NV_gpu_affinity
		total = loaded = 0;
		wglEnumGpusNV = (PFNWGLENUMGPUSNVPROC)GetProc("wglEnumGpusNV", total, loaded);
		wglEnumGpuDevicesNV = (PFNWGLENUMGPUDEVICESNVPROC)GetProc("wglEnumGpuDevicesNV", total, loaded);
		wglCreateAffinityDCNV = (PFNWGLCREATEAFFINITYDCNVPROC)GetProc("wglCreateAffinityDCNV", total, loaded);
		wglEnumGpusFromAffinityDCNV = (PFNWGLENUMGPUSFROMAFFINITYDCNVPROC)GetProc("wglEnumGpusFromAffinityDCNV", total, loaded);
		wglDeleteDCNV = (PFNWGLDELETEDCNVPROC)GetProc("wglDeleteDCNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_NV_gpu_affinity" << std::endl;
	#endif
		// WGL_NV_present_video
		total = loaded = 0;
		wglEnumerateVideoDevicesNV = (PFNWGLENUMERATEVIDEODEVICESNVPROC)GetProc("wglEnumerateVideoDevicesNV", total, loaded);
		wglBindVideoDeviceNV = (PFNWGLBINDVIDEODEVICENVPROC)GetProc("wglBindVideoDeviceNV", total, loaded);
		wglQueryCurrentContextNV = (PFNWGLQUERYCURRENTCONTEXTNVPROC)GetProc("wglQueryCurrentContextNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_NV_present_video" << std::endl;
	#endif
		// WGL_NV_swap_group
		total = loaded = 0;
		wglJoinSwapGroupNV = (PFNWGLJOINSWAPGROUPNVPROC)GetProc("wglJoinSwapGroupNV", total, loaded);
		wglBindSwapBarrierNV = (PFNWGLBINDSWAPBARRIERNVPROC)GetProc("wglBindSwapBarrierNV", total, loaded);
		wglQuerySwapGroupNV = (PFNWGLQUERYSWAPGROUPNVPROC)GetProc("wglQuerySwapGroupNV", total, loaded);
		wglQueryMaxSwapGroupsNV = (PFNWGLQUERYMAXSWAPGROUPSNVPROC)GetProc("wglQueryMaxSwapGroupsNV", total, loaded);
		wglQueryFrameCountNV = (PFNWGLQUERYFRAMECOUNTNVPROC)GetProc("wglQueryFrameCountNV", total, loaded);
		wglResetFrameCountNV = (PFNWGLRESETFRAMECOUNTNVPROC)GetProc("wglResetFrameCountNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_NV_swap_group" << std::endl;
	#endif
		// WGL_NV_vertex_array_range
		total = loaded = 0;
		wglAllocateMemoryNV = (PFNWGLALLOCATEMEMORYNVPROC)GetProc("wglAllocateMemoryNV", total, loaded);
		wglFreeMemoryNV = (PFNWGLFREEMEMORYNVPROC)GetProc("wglFreeMemoryNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_NV_vertex_array_range" << std::endl;
	#endif
		// WGL_NV_video_capture
		total = loaded = 0;
		wglBindVideoCaptureDeviceNV = (PFNWGLBINDVIDEOCAPTUREDEVICENVPROC)GetProc("wglBindVideoCaptureDeviceNV", total, loaded);
		wglEnumerateVideoCaptureDevicesNV = (PFNWGLENUMERATEVIDEOCAPTUREDEVICESNVPROC)GetProc("wglEnumerateVideoCaptureDevicesNV", total, loaded);
		wglLockVideoCaptureDeviceNV = (PFNWGLLOCKVIDEOCAPTUREDEVICENVPROC)GetProc("wglLockVideoCaptureDeviceNV", total, loaded);
		wglQueryVideoCaptureDeviceNV = (PFNWGLQUERYVIDEOCAPTUREDEVICENVPROC)GetProc("wglQueryVideoCaptureDeviceNV", total, loaded);
		wglReleaseVideoCaptureDeviceNV = (PFNWGLRELEASEVIDEOCAPTUREDEVICENVPROC)GetProc("wglReleaseVideoCaptureDeviceNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_NV_video_capture" << std::endl;
	#endif
		// WGL_NV_video_output
		total = loaded = 0;
		wglGetVideoDeviceNV = (PFNWGLGETVIDEODEVICENVPROC)GetProc("wglGetVideoDeviceNV", total, loaded);
		wglReleaseVideoDeviceNV = (PFNWGLRELEASEVIDEODEVICENVPROC)GetProc("wglReleaseVideoDeviceNV", total, loaded);
		wglBindVideoImageNV = (PFNWGLBINDVIDEOIMAGENVPROC)GetProc("wglBindVideoImageNV", total, loaded);
		wglReleaseVideoImageNV = (PFNWGLRELEASEVIDEOIMAGENVPROC)GetProc("wglReleaseVideoImageNV", total, loaded);
		wglSendPbufferToVideoNV = (PFNWGLSENDPBUFFERTOVIDEONVPROC)GetProc("wglSendPbufferToVideoNV", total, loaded);
		wglGetVideoInfoNV = (PFNWGLGETVIDEOINFONVPROC)GetProc("wglGetVideoInfoNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_NV_video_output" << std::endl;
	#endif
		// WGL_OML_sync_control
		total = loaded = 0;
		wglGetSyncValuesOML = (PFNWGLGETSYNCVALUESOMLPROC)GetProc("wglGetSyncValuesOML", total, loaded);
		wglGetMscRateOML = (PFNWGLGETMSCRATEOMLPROC)GetProc("wglGetMscRateOML", total, loaded);
		wglSwapBuffersMscOML = (PFNWGLSWAPBUFFERSMSCOMLPROC)GetProc("wglSwapBuffersMscOML", total, loaded);
		wglSwapLayerBuffersMscOML = (PFNWGLSWAPLAYERBUFFERSMSCOMLPROC)GetProc("wglSwapLayerBuffersMscOML", total, loaded);
		wglWaitForMscOML = (PFNWGLWAITFORMSCOMLPROC)GetProc("wglWaitForMscOML", total, loaded);
		wglWaitForSbcOML = (PFNWGLWAITFORSBCOMLPROC)GetProc("wglWaitForSbcOML", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for WGL_OML_sync_control" << std::endl;
	#endif
	}

	bool load(nitisa::Version2 *version, PlatformData *pd)
	{
		if (!Loaded)
		{
			Loaded = true;
			WNDCLASSEX cinfo;
			memset(&cinfo, 0, sizeof(WNDCLASSEX));
			cinfo.cbSize = sizeof(WNDCLASSEX);
			cinfo.hCursor = LoadCursorW(0, IDC_ARROW);
			cinfo.hInstance = pd ? pd->instance : nullptr;
			cinfo.lpfnWndProc = DefWindowProc;
			cinfo.lpszClassName = L"OpenGLTempWindowClass";
			cinfo.style = CS_CLASSDC | CS_DBLCLKS | CS_OWNDC;
			if (RegisterClassExW(&cinfo))
			{
				HWND window{ CreateWindowExW(WS_EX_OVERLAPPEDWINDOW, cinfo.lpszClassName, L"OpenGL", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, 0, cinfo.hInstance, 0) };
				if (window)
				{
					HDC dc{ GetDC(window) };
					if (dc)
					{
						PIXELFORMATDESCRIPTOR pf;
						memset(&pf, 0, sizeof(PIXELFORMATDESCRIPTOR));
						pf.nSize = sizeof(PIXELFORMATDESCRIPTOR);
						pf.nVersion = 1;
						pf.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
						pf.iPixelType = PFD_TYPE_RGBA;
						pf.cColorBits = 32;
						pf.cDepthBits = 24;
						pf.cStencilBits = 8;
						pf.iLayerType = PFD_MAIN_PLANE;
						int pf_index{ ChoosePixelFormat(dc, &pf) };
						HGLRC glc;
						if (pf_index && SetPixelFormat(dc, pf_index, &pf) && (glc = wglCreateContext(dc)))
						{
							if (wglMakeCurrent(dc, glc))
							{
								if (Module = LoadLibraryA("opengl32.dll"))
								{
									LoadProcedures();
									if (glGetIntegerv)
									{
										glGetIntegerv(GL_MAJOR_VERSION, &Version.Major);
										glGetIntegerv(GL_MINOR_VERSION, &Version.Minor);
									}
									LoadResult = true;
								}
							}
							wglMakeCurrent(0, 0);
							wglDeleteContext(glc);
						}
						ReleaseDC(window, dc);
					}
					DestroyWindow(window);
				}
				UnregisterClassW(cinfo.lpszClassName, cinfo.hInstance);
			}
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
		if (Module)
		{
			FreeLibrary(Module);
			Module = nullptr;
		}
		Loaded = LoadResult = false;
		Version = nitisa::Version2{ 0, 0 };
	}
}
#endif