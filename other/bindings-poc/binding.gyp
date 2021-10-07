{
  "targets": [
    {
      "sources": ["./bindings/module_01.c"],
      "target_name": "module_01"
    },
    {
      "sources": ["./bindings/module_02.c"],
      "target_name": "module_02"
    },
    {
      "sources": ["./bindings/module_03.c"],
      "target_name": "module_03"
    },
    {
      "sources": ["./bindings/module_04.cc"],
      "target_name": "module_04",
      'include_dirs': ["<!@(node -p \"require('node-addon-api').include\")"],
      'dependencies': ["<!(node -p \"require('node-addon-api').gyp\")"],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
    },
    {
      "sources": ["./bindings/module_05.cc"],
      "target_name": "module_05",
      'include_dirs': ["<!@(node -p \"require('node-addon-api').include\")"],
      'dependencies': ["<!(node -p \"require('node-addon-api').gyp\")"],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
    },
    {
      "sources": ["./bindings/module_06.cc"],
      "target_name": "module_06",
      'include_dirs': ["<!@(node -p \"require('node-addon-api').include\")"],
      'dependencies': ["<!(node -p \"require('node-addon-api').gyp\")"],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
    },
    {
      "sources": ["./bindings/module_07.c"],
      "target_name": "module_07"
    }
  ]
}
