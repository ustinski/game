QT += opengl

QMAKE_LFLAGS += -lSDL2 -lSDL2_mixer -lBox2D

SOURCES += \
    main.cpp \
    glwidget.cpp \
    button.cpp \
    mesh.cpp \
    cannon.cpp \
    scope.cpp \
    circle.cpp \
    bubble.cpp \
    cannonball.cpp \
    animatedobjects.cpp \
    gameobjects.cpp \
    fontrenderer.cpp \
    menu.cpp \
    gl.cpp \
    refraction.cpp \
    background.cpp \
    wavfile.cpp \
    sdlmixer.cpp \
    window.cpp \
    physics.cpp \
    listener.cpp

HEADERS += \
    glwidget.h \
    button.h \
    mesh.h \
    cannon.h \
    scope.h \
    circle.h \
    bubble.h \
    cannonball.h \
    animatedobjects.h \
    gameobjects.h \
    fontrenderer.h \
    menu.h \
    gl.h \
    refraction.h \
    background.h \
    wavfile.h \
    sdlmixer.h \
    window.h \
    physics.h \
    listener.h

RESOURCES += \
    shaders.qrc \
    textures.qrc \
    font.qrc \
    sounds.qrc


# TODO:
# more score for double shots, add bonus bubbles (should be hit in some time, others should not be hit), add bubbles that shouldn't be hit
# join bubbles when they collide?
# more score for hits with 1 ball
# add cleanup functions


# particles
# uncomment //cannonball.clear(); ?
# replace numbers with const
# remove width and height from mesh arguments

# commit:
# fixed box2d update
# pointer is in center at start

