// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"

namespace nitisa
{
	class ISocket
	{
	protected:
		ISocket() = default;
		~ISocket() = default;
		ISocket(const ISocket &other) = delete;
		ISocket(ISocket &&other) = delete;
		ISocket &operator=(const ISocket &other) = delete;
		ISocket &operator=(ISocket &&other) = delete;
	public:
		enum class ErrorType // Error types
		{
			InvalidHandle,
			NotEnoughMemory,
			InvalidParameter,
			OperationAborted,
			IOIncomplete,
			IOPending,
			InterruptedCall,
			InvalidFileHandle,
			PermissionDenied,
			BadAddress,
			InvalidArgument,
			TooManyOpenedFiles,
			OperationInProgress,
			OperationOnNonSocket,
			DestinationAddressRequird,
			MessageTooLong,
			WrongProtocolType,
			BadProtocolOption,
			ProtocolNotSupported,
			SocketTypeNotSupported,
			OperationNotSupported,
			ProtocolFamilyNotSupported,
			AddressfamilyNotSupported,
			AddressInUse,
			CannotAssignAddress,
			NetworkDown,
			NetworkUnreachable,
			NetwordDropConnection,
			SoftwareConnectionAbort,
			ConnectionResetByPeer,
			NoBufferSpaceAvailable,
			SocketAlreadyConnected,
			SocketNotConnected,
			CannotSendAfterShutdown,
			TooManyReferences,
			ConnectionTimeout,
			ConnectionRefused,
			CannotTranslateName,
			NameTooLong,
			HostDown,
			NoRouteToHost,
			DirectoryNotEmpty,
			TooManyProcesses,
			UserQuotaExceeded,
			DiskQuotaExceeded,
			StaleFileHandleReference,
			ItemIsRemote,
			NetworkSubsystemUnavailable,
			LibraryVersionOutOfRange,
			NoStartup,
			GracefulShutdownInProgress,
			NoMoreResults,
			Callcancelled,
			ProcedureCallTableInvalid,
			ServiceProviderInvalid,
			ServiceProviderFailedToInitialize,
			SystemCallFailed,
			ServiceNotFound,
			ClassTypeNotFound,
			CallCancelled,
			DatabaseQueryRefused,
			HostNotFound,
			NonAuthoritativeHostNotFound,
			NonRecoverableError,
			NoDataRecord,
			QoSReceivers,
			QoSSenders,
			NoQoSSenders,
			NoQoSReceivers,
			QoSRequestConfirmed,
			QoSAdmissionError,
			QoSPolicyFailed,
			QoSBadStyle,
			QoSBadObject,
			QoSTrafficControlError,
			QoSGenericError,
			QoSServiceTypeError,
			QoSFlowspecError,
			InvalidQoSProviderBuffer,
			InvalidQoSFilterStyle,
			InvalidQoSFilterType,
			IncorrectQoSFilterCount,
			InvalidQoSObjectLength,
			InvalidQoSFlowCount,
			UnrecognizedQoSObject,
			InvalidQoSPolicyObject,
			InvalidQoSFlowDescriptor,
			InvalidQoSProviderFlowSpec,
			InvalidQoSProviderFilterSpec,
			InvalidQoSShapeDiscardModeObject,
			InvalidQoSShapingRateObject,
			ReservedPolicyQoSElementType,

			Unknown
		};

		enum class DataExist // Data availability
		{
			Error,
			Disconnected,
			Exist,
			None
		};
	public:
		virtual AnsiString getLocalIp() = 0; // Return local IP address
		virtual AnsiString getRemoteIp() = 0; // Return remote IP address
		virtual int getLocalPort() = 0; // Return local port
		virtual int getRemotePort() = 0; // Return remote port

		virtual void Release() = 0; // Close connection and destroy itself
	};
}