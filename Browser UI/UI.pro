TEMPLATE  = app
LANGUAGE  = C++
CONFIG	 += console precompile_header
CONFIG   -= app_bundle

TEMPLATE    = app

FORMS       = mainwindow.ui \
              FTP_server_options.ui \
			  FTP_client_options.ui \
			  viewer_options.ui

HEADERS     = UI.h \
			  config.h \
			  server_options_dialog.h \
			  client_options_dialog.h \
			  viewer_options_dialog.h
			  
SOURCES     = loader.cpp \
              UI.cpp \
			  config.cpp \
			  server_options_dialog.cpp \
			  client_options_dialog.cpp	 \ 
			  viewer_options_dialog.cpp
			  
RESOURCES   = iconres.qrc