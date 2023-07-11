{
  "targets": [
    {
      "target_name": "binding",
      "sources": [ 
        "src/node/addon.cc",
        "src/node/entry.cc",
        "src/api.cc",
        "src/img-get.cc"  
      ],
      "include_dirs" : [
        "<!(node -e \"require('nan')\")"
      ]
      # "include_dirs": [
      #   "node_modules/nan"
      # ]
    }
  ]
}