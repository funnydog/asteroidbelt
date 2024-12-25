deps = []
deps += dependency('glew', required : true, fallback : ['glew', 'glew_dep'])
deps += dependency('glfw3', required : true, fallback : ['glfw', 'glfw_dep'])
deps += dependency('glm', required : true, fallback : ['glm', 'glm_dep'])
deps += dependency('freetype2', required : true, fallback : ['freetype2', 'freetype_dep'])
deps += dependency('openal', required : true, fallback : ['openal-soft', 'openal_dep'])

srcs = [
  # application
  'application.cpp',
  'asteroidbelt.cpp',

  # views
  'viewstack.cpp',
  'titleview.cpp',
  'gameview.cpp',
  'gameoverview.cpp',

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
