{
  "targets": [
    {
      "sources": [
        "./bindings/bus.c",
        "./bindings/custom_ime.c",
        "./bindings/engine.c",
        "./bindings/lookup_table.c",
        "./bindings/module.c",
        "./bindings/property.c",
        "./bindings/service.c",
        "./bindings/share.c",
        "./bindings/text.c",
      ],
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
