freetype2 = dependency('freetype2')
glew = dependency('glew')
glfw3 = dependency('glfw3')
glm = dependency('glm')
opengl = dependency('gl')
openal = dependency('openal')
vorbisfile = dependency('vorbisfile')

deps = [
  freetype2,
  glew,
  glfw3,
  glm,
  openal,
  vorbisfile,
  opengl,
]

srcs = [
  # application
  'application.cpp',
  'asteroidbelt.cpp',

  # views
  'viewstack.cpp',
  'titleview.cpp',
  'gameview.cpp',

  'sprite.cpp',
  'enemy.cpp',
  'particle.cpp',
  'starfield.cpp',
  'asteroidmanager.cpp',
  'shotmanager.cpp',
  'playermanager.cpp',
  'enemymanager.cpp',
  'explosionmanager.cpp',
  'collisionmanager.cpp',

  # graphics
  'camera.cpp',
  'eventqueue.cpp',
  'font.cpp',
  'rendertarget.cpp',
  'shader.cpp',
  'texture.cpp',
  'window.cpp',

  # audio
  'audiodevice.cpp',
  'soundfile.cpp',
  'soundfilewav.cpp',
  'soundfileogg.cpp',
  'soundbuffer.cpp',
  'soundsource.cpp',
  'sound.cpp',
  # utilities / third party
  'alcheck.cpp',
  'glcheck.cpp',
  'stb_image.cpp',
  'utility.cpp',
]

exe = executable(
  'asteroidbelt',
  sources: srcs,
  dependencies: deps,
  install : true
)
