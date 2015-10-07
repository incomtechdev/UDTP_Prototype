TEMPLATE  = app
LANGUAGE  = C++
CONFIG	 += console precompile_header
CONFIG   -= app_bundle
QT       += widgets

TEMPLATE    = app

FORMS       = mainwindow.ui \
              FTP_server_options.ui \
			  FTP_client_options.ui \
			  viewer_options.ui \
			  copy.ui

HEADERS     = UI.h \
			  config.h \
			  server_options_dialog.h \
			  client_options_dialog.h \
			  viewer_options_dialog.h \
			  progress_copy_dialog.h \
			  FTP_server_thread.h
			  
SOURCES     = loader.cpp \
              UI.cpp \
			  config.cpp \
			  server_options_dialog.cpp \
			  client_options_dialog.cpp	 \ 
			  viewer_options_dialog.cpp \
			  progress_copy_dialog.cpp \
			  FTP_server_thread.cpp
			  
RESOURCES   = iconres.qrc