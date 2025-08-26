#include "Nitisa/Interfaces/IClientSocket.h" // Include client socket interface definition
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
			IFormMain(CWindow::Create(), CRenderer::Create()) // We just call parent constructor and pass new window and renderer objects to it
		{

		}

		// This method will be called when we click on "ButtonStart" button. We only clear log and start TCP server here
		void CFormMain::ButtonStart_OnClick(IControl *sender)
		{
			m_pMemoLog->setText(L""); // Clear the log
			m_pTCPServer->setPort(m_pUpDownPort->getValue()); // Set selected port to TCPServer component
			if (m_pTCPServer->setActive(true)) // Try to activate TCP server
			{
				m_pMemoLog->AddLine(L"TCP server started at port " + ToString(m_pTCPServer->getPort())); // Add to log that server has successfully started
				m_pButtonStart->setEnabled(false); // Disable start button to prevent starting already started server
				m_pButtonStop->setEnabled(true); // Enable stop server button
			}
			else // If starting failed, write it to log
				m_pMemoLog->AddLine(L"Failed to start TCP server");
		}

		// This method will be called when we click on "ButtonStop" button. We only stop TCP server here
		void CFormMain::ButtonStop_OnClick(IControl *sender)
		{
			m_pTCPServer->setActive(false); // Deactivate TCP server
			m_pButtonStop->setEnabled(false); // Disable stop server button
			m_pButtonStart->setEnabled(true); // Enable start server button
			m_pMemoLog->AddLine(L"Server stopped"); // Write information about stopping into the log
		}

		// This method will be called periodically
		void CFormMain::Timer_OnTimer(IComponent *sender)
		{
			m_sSync.lock(); // We access resources which are also could be changed in another thread, so the synchronization is required
			for (auto log : m_aLogs) // Move logs from temporary storage to Memo control
				m_pMemoLog->AddLine(log);
			m_aLogs.clear();
			m_sSync.unlock(); // Finish synchronious access
			cast<IListItemStatusPanelLabel*>(m_pStatusBar->getItem(0))->setCaption(ToString(m_pTCPServer->getClientCount()) + L" connections"); // Update status bar to show actually connected count of users
		}

		// This method will be called each time the connected to our TCP server client has some data to read
		void CFormMain::TCPServer_OnClientHaveData(standard::ITCPServer *sender, standard::ITCPServer::IClient *client, bool &disconnect)
		{
			bool is_read_messages; // Our server supports 2 types of request: read messages and send message
			client->getSocket()->Read(is_read_messages); // Each request to the server should start from identification of message type
			if (is_read_messages) // If client has requested a list of messages
			{
				// Client should send last message id it have to the server know which messages to send back
				int last_id;
				client->getSocket()->Read(last_id);
				// Prepare list of messages not forgetting about synchronization when accessing resources because this method is called from thread different from main one
				std::vector<MESSAGE> messages;
				m_sSync.lock();
				for (auto msg : m_aMessages)
					if (msg.Id > last_id)
						messages.push_back(msg);
				m_aLogs.push_back(L"Client requested messages with ID greater than " + ToString(last_id) + L". " + ToString(messages.size()) + L" found"); // Add log message
				m_sSync.unlock();
				// Write response to buffer and then send back all at once
				client->getSocket()->OpenWriteBuffer();
				client->getSocket()->Write((int)messages.size());
				for (auto msg : messages)
				{
					client->getSocket()->Write(msg.Id);
					client->getSocket()->Write(msg.User);
					client->getSocket()->Write(msg.Message);
				}
				client->getSocket()->CloseWriteBuffer(); // Here is the place where data will be send back to the client
			}
			else // If user sends a message
			{
				// Read user name and message
				String user, message;
				client->getSocket()->Read(user);
				client->getSocket()->Read(message);
				// Add message to the list and update log. As usually synchronize access to the resources
				m_sSync.lock();
				m_aMessages.push_back({ (int)m_aMessages.size() + 1, user, message });
				m_aLogs.push_back(L"New message from '" + user + L"'"); // Add log message
				m_sSync.unlock();
			}
		}
	}
}