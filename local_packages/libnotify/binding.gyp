{
  "targets": [
    {
      "sources": ["./bindings/module.c"],
      "target_name": "module",
      "include_dirs": [
        "<!@(pkg-config libnotify --cflags-only-I | sed s/-I//g)"
      ],
      "libraries": [
        "<!@(pkg-config libnotify --libs)"
      ]
    }
  ]
}
