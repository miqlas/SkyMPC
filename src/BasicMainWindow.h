#ifndef BASICMAINWINDOW_H
#define BASICMAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include "MusicPlayerClient.h"

class Host;
class Command;
class QToolButton;
class QListWidget;
class QComboBox;

enum class PlayingStatus {
	Unknown,
	Stop,
	Play,
	Pause,
};

class BasicMainWindow : public QMainWindow {
	Q_OBJECT
	friend class EditPlaylistDialog;
protected:
	struct Private;
	Private *pv;
	MusicPlayerClient *mpc();
	static QString makeStyleSheetText();
	void releaseMouseIfGrabbed();
	void stopSleepTimer();
	void stopStatusThread();
	void execSleepTimerDialog();

	int currentPlaylistCount();
	static QString textForExport(const MusicPlayerClient::Item &item);

	void updatePlayingStatus();
	virtual void updateServersComboBox() {}
	virtual void setPageConnected() {}
	virtual void updateTreeTopLevel() {}
	virtual void setPageDisconnected() {}
	virtual void setVolumeEnabled(bool) {}
	virtual void clearTreeAndList() {}
	void displayStopStatus();

	virtual void setRepeatEnabled(bool f);
	virtual void setSingleEnabled(bool f);
	virtual void setConsumeEnabled(bool f);
	virtual void setRandomEnabled(bool f);

	virtual void displayCurrentSongLabels(const QString & /*title*/, const QString & /*artist*/, const QString & /*disc*/) = 0;
	virtual void seekProgressSlider(double /*elapsed*/, double /*total*/) {}
	virtual void displayProgress(const QString & /*text*/) {}
	virtual void updatePlayIcon() {}
	virtual void updatePlaylist() {}
	virtual void updateCurrentSongInfo() {}
	void invalidateCurrentSongIndicator();
	void displayProgress(double elapsed);

	QString serverName() const;
	void showNotify(const QString &text);
	void showError(const QString &text);
	void update(bool mpdupdate);
	void checkDisconnected();
	void execSongProperty(const QString &path, int listrow, bool addplaylist);
	void clearPlaylist();
	void startSleepTimer(int mins);
	void doQuickSave1();
	void doQuickSave2();
	void doQuickLoad1();
	void doQuickLoad2();
	virtual void doUpdateStatus();
	void updatePlayIcon(PlayingStatus status, QToolButton *button, QAction *action);
	virtual void displayExtraInformation(const QString &text2, const QString &text3) = 0;
	void timerEvent(QTimerEvent *);
	static void updatePlaylist(QListWidget *listwidget, QList<MusicPlayerClient::Item> *items);
	static void makeServersComboBox(QComboBox *cbox, const QString &firstitem, const Host &current_host);
	void onServersComboBoxIndexChanged(QComboBox *cbox, int index);
	virtual void execConnectionDialog() = 0;
	virtual void updateClock(QString const & /*text*/) {}
	QString currentSongTitle() const;
public:
	BasicMainWindow(QWidget *parent);
	~BasicMainWindow();
	virtual void eatMouse();
	virtual bool isAutoReconnectAtStartup();
	virtual void preexec();
	void connectToMPD(const Host &host);
	bool isPlaying() const;
	void startStatusThread();
	void addToPlaylist(const QString &path, int to, bool update);
	void play();
	void pause();
	void stop();
	void play(bool toggle);
	void disconnectNetwork();
	void loadPlaylist(const QString &name, bool replace);
	bool savePlaylist(const QString &name, bool warning_if_needed);
	void execAddLocationDialog();

	static BasicMainWindow *findMainWindow(QObject *hint = nullptr);
	static bool isTinyMode(QObject *hint = nullptr);

	void unify();
	bool validateForSavePlaylist();
	void addPlaylsitToPlaylist(QString const &path, int to);
private slots:
	void onVolumeChanged();
	void onUpdateStatus();
};

enum {
	EVENT_FocusChanged = QEvent::User,
	EVENT_QueryInfo,
};

#endif // BASICMAINWINDOW_H
