#include "include/FileManager.h"
#include "include/Magazine.h"
#include "include/Subscriber.h"

#include <QTextStream>
#include <QFileInfo>
#include <thread>

FileManager::~FileManager()
{
	for (const auto& it : subscribers)
		delete it;

	for (const auto& it : magazines)
		delete it;
}

FileManager& FileManager::instance()
{
	static FileManager obj;
	return obj;
}

void FileManager::printMagazines()
{
	QTextStream(stdout) << "\tMAGAZINES" << endl;

	qint32 i = 0;

	for (const auto& magazine : magazines)
	{
		if (magazine->getCondition() != Magazine::Condition::DeleteWin)
		{
			QTextStream(stdout) << "\t" << i++ << " ---> " << magazine->getName() << endl;
		}
		else if (magazine->getCondition() == Magazine::Condition::DeleteWin)
		{
			QTextStream(stdout) << "\t" << i++ << " ---> " << magazine->getName() << " DELETE WINAPI" << endl;
		}
	}
}

void FileManager::printSubscribers()
{
	QTextStream(stdout) << "\tSUBSCRIBERS" << endl;

	qint32 i = 0;

	for (const auto& subscriber : subscribers)
	{
		if (subscriber->getCondition() != Subscriber::Condition::MagazineDelWinApi)
		{
			QTextStream(stdout) << "\t" << i++ << " ---> " << subscriber->getName() << endl;
		}
		else if (subscriber->getCondition() == Subscriber::Condition::MagazineDelWinApi)
		{
			QTextStream(stdout) << "\t" << i++ << " ---> " << subscriber->getName() << " MAGAZINE WAS DELETE WINAPI" << endl;
		}
	}
}

FileManager& FileManager::startTerminalThread()
{
	std::thread terminalThread(&FileManager::terminal, this);

	terminalThread.detach();

	return *this;
}

FileManager& FileManager::startCheckThread()
{
	std::thread checkThread(&FileManager::check, this);

	checkThread.detach();

	return *this;
}

void FileManager::terminal()
{
	QTextStream cin(stdin), cout(stdout);

	forever
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		QString command;

		bool isCommand = false;

		while (!isCommand)
		{
			cout << "Input the command: " << flush;
			command = cin.readLine().trimmed().toLower();

			std::find(commands.begin(), commands.end(), command) != commands.end() ? isCommand = true : isCommand = false;

			if (!isCommand && command.isEmpty())
			{
				command = commands[4];
				isCommand = true;
			}
		}

		// add subscriber
		if (command == commands[0])
		{
			QString name;
			bool isAdd = false;

			while (!isAdd)
			{
				cout << '\t' << "Input subscriber: " << flush;
				name = cin.readLine().trimmed();

				isAdd = true;

				for (const auto& it : subscribers)
				{
					if (it->getName() == name)
					{
						cout << "\t" << name << " exists!" << endl;
						isAdd = false;
						break;
					}
				}

				if (isAdd)
					emit addSubscriber(name);
			}

			continue;
		}

		// add magazine
		if (command == commands[1])
		{
			QString path;
			bool isAdd = false;

			while (!isAdd)
			{
				cout << '\t' << "Input magazine: " << flush;
				path = cin.readLine().trimmed();

				if (!path.isEmpty())
				{
					emit addMagazine(path);
					isAdd = true;
				}
			}

			continue;
		}

		// connect
		if (command == commands[2])
		{
			bool isConnect = false;

			this->printMagazines();
			this->printSubscribers();

			while (!isConnect)
			{
				qint32 idMagazine, idSubscriber;

				cout << "\tInput ID magazine which you want to connect: " << flush;

				idMagazine = cin.readLine().trimmed().toInt();

				cout << "\tInput ID subscriber which you want to connect: " << flush;

				idSubscriber = cin.readLine().trimmed().toInt();

				if ((idMagazine >= 0 && idMagazine < magazines.size()) && (idSubscriber >= 0 && idSubscriber < subscribers.size()))
				{
					if (!subscribers[idSubscriber]->subscribe())
					{
						emit connect(idMagazine, idSubscriber);
						isConnect = true;
					}
					else
						cout << "\tSubscriber " << subscribers[idSubscriber]->getName() << " already a subscriber! " << subscribers[idSubscriber]->getMagazine() << endl;
				}
				else
				{
					cout << "\t" << "Error connect!" << endl;
				}
			}

			continue;
		}

		// list
		if (command == commands[3])
		{
			if (!magazines.isEmpty())
			{
				this->printMagazines();
			}
			else
			{
				cout << "\tNO MAGAZINES!" << endl;
			}

			if (!subscribers.isEmpty())
			{
				this->printSubscribers();
			}
			else
			{
				cout << "\tNO SUBSCRIBERS!" << endl;
			}

			continue;
		}

		// help
		if (command == commands[4])
		{
			QStringList help = QString("Add subscriber - added subscriber\nAdd magazine - added magazine\nConnect - connections subscriber with magazine\nList - list of subscribers and magazines\nHelp - list of commands\nDelete magazine - delete magazine\nDelete Subscriber - delete subscriber\nGet counter - to know size of subscribers by magazine\mResign - change magazine\nClear - cls your console").split('\n');

			foreach(const auto & it, help)
			{
				cout << '\t' << it << endl;
			}

			continue;
		}

		// size
		if (command == commands[5])
		{
			bool isSize = false;

			if (!subscribers.isEmpty())
			{
				this->printSubscribers();

				while (!isSize)
				{
					cout << "\tEnter the id of the subscriber from whom you want to find out the size of magazine: " << flush;

					qint32 idSubscriber = cin.readLine().trimmed().toInt();

					if (idSubscriber >= 0 && idSubscriber < subscribers.size())
					{
						if (subscribers[idSubscriber]->subscribe())
						{
							cout << "\t\tSize is " << QFileInfo(subscribers[idSubscriber]->getMagazine()).size() << " byte" << endl;
							isSize = true;
						}
						else
						{
							cout << "\t\tSubscriber has not magazine!" << endl;
							break;
						}
					}
					else
					{
						cout << "\t\tWrong id!" << endl;
					}
				}
			}
			else
			{
				cout << "\tNO SUBSCRIBES!" << endl;
			}

			continue;
		}

		// delete magazine
		if (command == commands[6])
		{
			if (magazines.isEmpty())
			{
				cout << "\tNO MAGAZINES!" << endl;
				continue;
			}

			this->printMagazines();

			cout << "\t\tInput number magazine which you want to delete: " << flush;

			bool isDel = false;

			while (!isDel)
			{
				qint32 idMagazine = cin.readLine().trimmed().toInt();

				if (idMagazine >= 0 && idMagazine < magazines.size())
				{
					emit deleteMagazine(idMagazine);

					isDel = true;
				}
			}

			continue;
		}

		// delete subscriber
		if (command == commands[7])
		{
			if (subscribers.isEmpty())
			{
				cout << "\tNO SUBSCRIBES!" << endl;
				continue;
			}

			this->printSubscribers();

			cout << "\t\tInput number of subcriber which you want to delete: " << flush;

			bool isDel = false;

			while (!isDel)
			{
				qint32 idSubscriber = cin.readLine().trimmed().toInt();

				if (idSubscriber >= 0 && idSubscriber < subscribers.size())
				{
					emit deleteSubscriber(idSubscriber);

					isDel = true;
				}
			}

			continue;
		}

		// get counter
		if (command == commands[8])
		{
			if (magazines.isEmpty())
			{
				cout << "\tNO MAGAZINES!" << endl;
				continue;
			}

			this->printMagazines();

			cout << "\t\tInput number magazine which you want to know counter: " << flush;

			bool isCounter = false;

			while (!isCounter)
			{
				qint32 idMagazine = cin.readLine().trimmed().toInt();

				if (idMagazine >= 0 && idMagazine < magazines.size())
				{
					emit getCounter(idMagazine);

					isCounter = true;
				}
			}

			continue;
		}

		// resign
		if (command == commands[9])
		{
			if (subscribers.isEmpty())
			{
				cout << "\tNO SUBSCRIBERS!" << endl;
				continue;
			}

			if (magazines.isEmpty())
			{
				cout << "\tNO MAGAZINES!" << endl;
				continue;
			}

			this->printMagazines();
			this->printSubscribers();

			cout << "\t\tInput number subscriber which you want to re-sign: " << flush;

			bool isResign = false;

			while(!isResign)
			{
				qint32 idSubscriber = cin.readLine().trimmed().toInt();

				if (idSubscriber >= 0 && idSubscriber < subscribers.size())
				{
					cout << "\t\tInput the idMagazine which you want to subscribe to: " << flush;

					qint32 idMagazine = cin.readLine().trimmed().toInt();

					if (idMagazine >= 0 && idMagazine < magazines.size())
					{
						emit resign(idSubscriber, idMagazine);

						isResign = true;
					}
				}
			}

			continue;
		}

		// clear
		if (command == commands[10])
		{
			emit clear();
		}
	}
}

void FileManager::check()
{
	forever
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		QTextStream cout(stdout);

		bool isCheck = false;

		if (!magazines.isEmpty())
		{
			for (const auto& magazine : magazines)
			{
				if (!QFileInfo(magazine->getName()).exists() && magazine->getCondition() == Magazine::Condition::Init)
				{
					cout << endl << "\t\t" << magazine->getName() << " was deleted with WinAPI" << endl;

					for (const auto& subscriber : subscribers)
					{
						subscriber->getCondition() = Subscriber::Condition::MagazineDelWinApi;
					}

					magazine->getCondition() = Magazine::Condition::DeleteWin;

					isCheck = true;
				}

				if (QFileInfo(magazine->getName()).exists() && magazine->getCondition() == Magazine::Condition::DeleteWin)
				{
					cout << endl << "\t\t" << magazine->getName() << " magazine has been restored!" << endl;

					for (const auto& subscriber : subscribers)
					{
						subscriber->getCondition() = Subscriber::Condition::Init;
					}

					magazine->getCondition() = Magazine::Condition::Init;

					isCheck = true;
				}
			}
		}

		if (isCheck)
			cout << "Input the command: " << flush;
	}
}

FileManager::FileManager() :
	QObject(nullptr),
	commands({
		"add subscriber",
		"add magazine",
		"connect",
		"list",
		"help",
		"size",
		"delete magazine",
		"delete subscriber",
		"get counter",
		"resign",
		"clear"
		})
{
	QObject::connect(this, &FileManager::addMagazine, [&](const QString& path)
		{
			if (QFileInfo(path).exists() && QFileInfo(path).isFile())
			{
				magazines.push_back(new Magazine(path));
				QTextStream(stdout) << "\t\tMagazine " << path << " was added!" << endl;
			}
			else
			{
				QTextStream(stdout) << "\t\tPath to magazine was not added!" << endl;
			}
		});

	QObject::connect(this, &FileManager::addSubscriber, [&](const QString& name)
		{
			if (!name.isEmpty())
			{
				subscribers.push_back(new Subscriber(name));
				QTextStream(stdout) << "\t\tSubscriber " << name << " was added!" << endl;
			}
			else
			{
				QTextStream(stdout) << "\t\tSubscriber was not added!" << endl;
			}
		});

	QObject::connect(this, &FileManager::connect, [&](const qint32& idMagazine, const qint32& idSubscriber)
		{
			if (!subscribers[idSubscriber]->subscribe())
			{
				magazines[idMagazine]->addSubscriber(subscribers[idSubscriber]);
				subscribers[idSubscriber]->getMagazine() = magazines[idMagazine]->getName();
				subscribers[idSubscriber]->subscribe() = true;

				QTextStream(stdout) << "\t\t" << magazines[idMagazine]->getName() << " was connect with " << subscribers[idSubscriber]->getName() << endl;
			}
			else
			{
				QTextStream(stdout) << "\t\tConnection error!" << endl;
			}
		});

	QObject::connect(this, &FileManager::deleteMagazine, [&](const qint32& index)
		{
			for (qint32 iter = 0; iter < magazines.size(); ++iter)
			{
				if (iter == index)
				{
					QTextStream(stdout) << "\t\t" << magazines[iter]->getName() << " was deleted!" << endl;

					for (const auto& subscriber : magazines[iter]->getSubscribers())
					{
						subscriber->getCondition() = Subscriber::Init;
						subscriber->getMagazine().clear();
						subscriber->subscribe() = false;
					}

					magazines.remove(iter);

					break;
				}
			}
		});

	QObject::connect(this, &FileManager::deleteSubscriber, [&](const qint32& index)
		{
			for (qint32 iter = 0; iter < subscribers.size(); ++iter)
			{
				if (iter == index)
				{
					QTextStream(stdout) << "\t\t" << subscribers[iter]->getName() << " was deleted!" << endl;

					for (qint32 iterMag = 0; iterMag < magazines.size(); ++iterMag)
					{
						for (qint32 iterSub = 0; iterSub < magazines[iterMag]->getSubscribers().size(); ++iterSub)
						{
							if (subscribers[index]->getName() == magazines[iterMag]->getSubscribers()[iterSub]->getName())
							{
								magazines[iterMag]->getSubscribers().remove(iterSub);
								magazines[iterMag]->getCounter()--;
							}
						}
					}

					subscribers.remove(iter);

					break;
				}
			}
		});

	QObject::connect(this, &FileManager::getCounter, [&](const qint32& index)
		{
			for (qint32 iter = 0; iter < magazines.size(); ++iter)
			{
				if (iter == index)
				{
					QTextStream(stdout) << "\t\tCounter " << magazines[iter]->getName() << " is equal " << magazines[iter]->getCounter() << endl;
					break;
				}
			}
		});

	QObject::connect(this, &FileManager::resign, [&](const qint32& idSubscriber, const qint32& idMagazine)
		{
			for (qint32 iter = 0; iter < subscribers.size(); ++iter)
			{
				if (iter == idSubscriber)
				{
					if (!subscribers[idSubscriber]->subscribe())
					{
						QTextStream(stdout) << "\t\tThe subscriber is not subscribed yet!" << endl;
					}
					else
					{
						for (qint32 mag = 0; mag < magazines.size(); ++mag)
						{
							if (magazines[mag]->getName() == subscribers[idSubscriber]->getMagazine())
							{
								for (qint32 sub = 0; sub < magazines[mag]->getSubscribers().size(); ++sub)
								{
									if (magazines[mag]->getSubscribers()[sub]->getName() == subscribers[idSubscriber]->getName())
									{
										magazines[mag]->getSubscribers().remove(sub);
										magazines[mag]->getCounter()--;
									}
								}
							}
						}
						
						magazines[idMagazine]->addSubscriber(subscribers[idSubscriber]);
						subscribers[idSubscriber]->getMagazine() = magazines[idMagazine]->getName();
						subscribers[idSubscriber]->subscribe() = true;
						subscribers[idSubscriber]->getCondition() = Subscriber::Condition::Init;

						QTextStream(stdout) << "\t\t" << magazines[idMagazine]->getName() << " was connect with " << subscribers[idSubscriber]->getName() << endl;
					}
				}
			}
		});

	QObject::connect(this, &FileManager::clear, []()
		{
			std::system("cls");
		});
}
