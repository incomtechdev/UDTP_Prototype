#include <map>
#include <QString>
#include <QFile>


using namespace std;

class UI_config
{
	QFile configfile;
	map<QString, QString> data;

	void setDataToFile(map<QString, QString>::iterator iter, const QString &dataValue);

public:
	UI_config(const QString &filename);
	~UI_config();

	QString getDataValue(const QString &dataname);
	void setDataValue(const QString &dataname, const QString &dataValue);

};