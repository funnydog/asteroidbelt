freetype2 = dependency('freetype2')
glew = dependency('glew')
glfw3 = dependency('glfw3')
glm = dependency('glm')
opengl = dependency('gl')

deps = [
  freetype2,
  glew,
  glfw3,
  glm,
  opengl,
]

srcs = [
  # application
  'application.cpp',
  'asteroidbelt.cpp',

  # views
  'viewstack.cpp',
  'titleview.cpp',

  'sprite.cpp',
  'starfield.cpp',

  # graphics
  'camera.cpp',
  'eventqueue.cpp',
  'font.cpp',
  'rendertarget.cpp',
  'shader.cpp',
  'texture.cpp',
  'window.cpp',

  # utilities / third party
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
