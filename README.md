
# Undefined Engine

## Summary

- [Undefined Engine](#undefined-engine)
  - [Summary](#summary)
  - [Contributors](#contributors)
  - [Presentation](#presentation)
- [Features](#features)
  - [Object/Component](#objectcomponent)
  - [Content Browser](#content-browser)
  - [Inspector](#inspector)
- [Screenshots](#screenshots)

## Contributors

- [Cyril](https://gitlabstudents.isartintra.com/c.khalil)
- [Paul](https://gitlabstudents.isartintra.com/p.bussy)
- [Lucas](https://gitlabstudents.isartintra.com/l.sarrazin)
  
## Presentation

This is our homemade engine realise in C++20, compile with MSVC v142 and had been made to be used in 64-bit Windows.

# Features

## Object/Component

You can add an object on your scene either by right clicking on the Graph scene window or by adding it in c++ with : SceneManager::YourScene->AddObject("ObjectName");

![thumbnail](https://media.discordapp.net/attachments/1017031699885989899/1243305619264372866/image.png?ex=6650fe17&is=664fac97&hm=b68ea2bc50aba922a214fd45b866e8a976252df9550efc7537f5e0a12584b544&=&format=webp&quality=lossless&width=490&height=361)

When you have your object you can add multiple components to your object (e.g : Collider, ModelRenderer, SoundSource, ...). you can do that by clicking on the add component button on the Inspector window or by adding it in c++ with : YourObject->AddComponent<PointLight>(param ...)

![thumbnail](https://media.discordapp.net/attachments/1017031699885989899/1243305619264372866/image.png?ex=6650fe17&is=664fac97&hm=b68ea2bc50aba922a214fd45b866e8a976252df9550efc7537f5e0a12584b544&=&format=webp&quality=lossless&width=490&height=361)

## Content Browser 

A content browser where you can see and open your project's files and folder like in the one from Windows.

![thumbnail](https://media.discordapp.net/attachments/1017031699885989899/1243305658598821969/image.png?ex=6650fe20&is=664faca0&hm=d439770cbc5c4e3ec7facc521ea1f1a99ac6c8f13805ff595764b00b62debfc0&=&format=webp&quality=lossless&width=1440&height=337)

## Inspector

In the Inspector you can see the properties and components properties of the selected object and you can modify them

![thumbnail](https://media.discordapp.net/attachments/1017031699885989899/1243305531364606012/image.png?ex=6650fe02&is=664fac82&hm=38c0d871a90ed59bca1fa3c6d7b96890234a0ba777bc694f802989c879b021db&=&format=webp&quality=lossless&width=368&height=623)

## Graph Scene

A Hierarchy of the Object in the scene where you can see parent/child object and select them.

![thumbnail](https://media.discordapp.net/attachments/1017031699885989899/1243309152168710245/image.png?ex=66510161&is=664fafe1&hm=0515f4a7a2942034331e1e9c5a58e217e174d9cf0e18acd6b59b008cbfec010a&=&format=webp&quality=lossless&width=283&height=317)

## Screenshots

![thumbnail](https://media.discordapp.net/attachments/1017031699885989899/1243305441702707311/image.png?ex=6650fdec&is=664fac6c&hm=439d7095e2596ace8eb9d84993a888f4cf06f9e4d47e620ee681396d9a78ead6&=&format=webp&quality=lossless&width=635&height=437)

![thumbnail](https://cdn.discordapp.com/attachments/1017031699885989899/1243305742652674128/image.png?ex=6650fe34&is=664facb4&hm=54b4d00948aea470092d757a6538a89149902ed73c537c5a3b5f4ddcc849c090&)