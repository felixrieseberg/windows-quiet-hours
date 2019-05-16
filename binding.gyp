{
  "targets": [
    {
      "target_name": "quiethours",
      "sources": [
        "lib/quiethours.cc"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
