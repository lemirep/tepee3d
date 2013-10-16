
TEMPLATE = subdirs

SUBDIRS = ManageDatabaseService \
          WebServiceManagerLibrary \
          FileDownloaderLibrary


message($$QMAKESPEC)

linux-g++-64 {
          SUBDIRS += LeapMotionControllerLibrary
}

linux-g++-32 {
          SUBDIRS += LeapMotionControllerLibrary
}

win32: {
    contains(QMAKE_HOST.arch, x86_64) {
          SUBDIRS += LeapMotionControllerLibrary
    }
}


OTHER_FILES += Documentation/how_to_service.qdoc
