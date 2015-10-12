#include "config.h"
#include <QStringList>
#include <QRegExp>

UI_config::UI_config(const QString &filename) : configfile(filename)
{
	string sss;

	if (configfile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QStringList confPair;
		pair<QString, QString> confParam;
		while (!configfile.atEnd())
		{
			confPair = QString(configfile.readLine()).trimmed().split("=");
			if (confPair.size() < 2) /// no "" in line
				continue;

			confPair[0] = confPair[0].trimmed();
			confPair[1] = confPair[1].trimmed();

			if ((confPair[1].size() == 0))
				confPair[1] = QString("-");

			confParam.first = confPair[0];
			confParam.second = confPair[1];
			data.insert(confParam);
		}
		configfile.close();
	}
}

UI_config::~UI_config()
{

}

QString UI_config::getDataValue(const QString &dataname)
{
	map<QString, QString>::iterator iter;
	iter = data.find(dataname);
	if (iter != data.end())
		return data.find(dataname)->second;
	else
		return QString("-");
}

void UI_config::setDataToFile(map<QString, QString>::iterator iter, const QString &dataValue)
{
	if (configfile.open(QIODevice::ReadOnly))
	{
		QString confStream = QString(configfile.readAll());
		configfile.close();
		int id = confStream.indexOf(iter->first + " " + iter->second);
		if (id != -1)
		{
			id = confStream.indexOf(iter->second, id + iter->first.size());
			if (id != -1)
			{
				confStream.remove(id, iter->second.size());
				confStream.insert(id, dataValue);
			}

			if (configfile.open(QIODevice::WriteOnly))
			{
				configfile.write(confStream.toUtf8());
				configfile.close();
			}
		}
	}
}

void UI_config::setDataValue(const QString &dataname, const QString &dataValue)
{
	map<QString, QString>::iterator iter;
	iter = data.find(dataname);
	if (iter != data.end())
	{
		setDataToFile(iter, dataValue);
		iter->second = dataValue;
	}
}