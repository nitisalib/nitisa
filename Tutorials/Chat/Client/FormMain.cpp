#include "NTL/Core/Utils.h" // Include some mathematical utilities like Min()/Max() functions
#include "Nitisa/Interfaces/IClientSocket.h" // Include client socket interface definition
#include "Nitisa/Interfaces/IDialogs.h" // Include dialogs interface declaration
#include "Nitisa/Interfaces/INetwork.h" // Include network interfaces declaration
#include "Platform/Core/Renderer.h" // Renderer class is here
#include "Platform/Core/Window.h" // Window class is here
#include "FormMain.h" // Our form declaration is here

namespace nitisa // All the forms should be in "nitisa" namespace
{
	namespace app // Our project form namespace. Can be changed in the Form Builder settings
	{
		using namespace standard; // We will use entities from the namespace of Standard Package often, so lets add this line to avoid writing "standard::" everywhere

		// Form's constructor
		CFormMain::CFormMain() :
			IFormMain(CWindow::Create(), CRenderer::Create()), // We just call parent constructor and pass new window and renderer objects to it
			m_iLastId{ 0 } // No message loaded yet
		{

		}

		// Process click on connect button
		void CFormMain::ButtonConnect_OnClick(IControl *sender)
		{
			m_pTCPClient->setServer(m_pEditServer->getText()); // Set server to TCPClient component
			m_pTCPClient->setPort(m_pUpDownPort->getValue()); // Set port to TCPClient component
			if (!m_pTCPClient->setActive(true)) // If failed to activate TCPClient(connect to server), just show an error dialog message and exit
			{
				Application->Dialogs->Error(L"Unable to connect");
				return;
			}
			m_pButtonConnect->setEnabled(false); // Disable connect button
			m_pButtonDisconnect->setEnabled(true); // Enable disconnect button
			m_pTimer->setEnabled(true); // Run timer
		}

		// Process click on disconnect button
		void CFormMain::ButtonDisconnect_OnClick(IControl *sender)
		{
			m_pTimer->setEnabled(false); // Stop timer
			m_pTCPClient->setActive(false); // Disconnect from server
			m_pButtonDisconnect->setEnabled(false); // Disable disconnect button
			m_pButtonConnect->setEnabled(true); // Enable connect button
		}

		// Timer method called periodically
		void CFormMain::Timer_OnTimer(IComponent *sender)
		{
			// Load new messages from server
			m_pTCPClient->getSocket()->Write(true); // true means we request list of messages
			m_pTCPClient->getSocket()->Write(m_iLastId); // Send last message Id we've got
			int count;
			m_pTCPClient->getSocket()->Read(count); // Read how much new message server found for us
			for (int i = 0; i < count; i++) // Load all messages server sent
			{
				int id;
				String user, message;
				m_pTCPClient->getSocket()->Read(id); // Read message Id
				m_pTCPClient->getSocket()->Read(user); // Read user name
				m_pTCPClient->getSocket()->Read(message); // Read message
				m_pMemoChat->AddLine(user + L": " + message); // Add message to Memo with all messages
				m_iLastId = ntl::Max<int>(m_iLastId, id); // Update last Id
			}
		}

		// Process key up on Edit control having the message to be send
		void CFormMain::EditMessage_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed)
		{
			if (m.Key == Key::Return && m_pTCPClient->isActive()) // Send only if the key is Enter and we connected to a server
			{
				String user{ Trim(m_pEditName->getText()) }, message{ Trim(m_pEditMessage->getText()) }; // Get clean(without spaces at the beginning and at the end) user name and message
				if (!user.empty() && !message.empty()) // Send only if both user name and message are specified
				{
					m_pTCPClient->getSocket()->Write(false); // false means we send new message to server
					m_pTCPClient->getSocket()->Write(user); // Send user name
					m_pTCPClient->getSocket()->Write(message); // Send message
					m_pEditMessage->setText(L""); // Clear message Edit control
				}
			}
		}
	}
}