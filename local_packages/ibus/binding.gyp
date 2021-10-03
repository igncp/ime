{
  "targets": [
    {
      "sources": ["./bindings/module.c"],
      "target_name": "module",
      "include_dirs": [
        "<!@(pkg-config ibus-1.0 --cflags-only-I | sed s/-I//g)"
      ],
      "libraries": [
        "<!@(pkg-config ibus-1.0 --libs)"
      ]
    }
  ]
}
