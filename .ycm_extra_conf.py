def Settings( **kwargs ):
  return {
    'flags': ['-x', 'c++', '-Wall', '-pedantic', '-Isrc',
    '-Iinclude',
    '-Igodot-cpp/gen/include',
    '-Igodot-cpp/gen/gdextension',
    '-Igodot-cpp/include',
    '-Igodot-cpp/gdextension',
    '-std=c++17', '-I/usr/include'],
  }
