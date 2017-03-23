{
  "targets": [
    {
      "target_name": "quiethours",
      "sources": [ ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      "conditions": [
        ['OS=="win"', {
          "sources": [ "lib/quiethours.cc" ],
        }]
      ]
    }
  ]
}
