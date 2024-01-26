================================================================================
    BIBLIOTHÈQUE MFC (MICROSOFT FOUNDATION CLASS) : Vue d'ensemble du projet WSJTXHelper
===============================================================================

L'Assistant Application a créé cette application WSJTXHelper pour vous. Cette application décrit non seulement les bases de l'utilisation de Microsoft Foundation Classes, mais est également un point de départ pour l'écriture de votre application.

Ce fichier contient un résumé du contenu de chacun des fichiers qui constituent votre application WSJTXHelper.

WSJTXHelper.vcxproj
    Il s'agit du fichier projet principal pour les projets VC++ générés à l'aide d'un Assistant Application. Il contient des informations sur la version de Visual C++ utilisée pour générer le fichier ainsi que des informations relatives aux plateformes, configurations et fonctionnalités du projet que vous avez sélectionnées dans l'Assistant Application.

WSJTXHelper.vcxproj.filters
    Il s'agit du fichier de filtres pour les projets VC++ générés à l'aide d'un Assistant Application. Il contient des informations sur l'association entre les fichiers de votre projet et les filtres. Cette association est utilisée dans l'IDE pour afficher le regroupement des fichiers qui ont des extensions similaires sous un nœud spécifique (par exemple, les fichiers ".cpp" sont associés au filtre "Fichiers sources").

WSJTXHelper.h
    Il s'agit du fichier d'en-tête principal pour l'application.
    Il comprend d'autres en-têtes spécifiques au projet (notamment Resource.h) et déclare la classe d'application CWSJTXHelperApp.

WSJTXHelper.cpp
    Il s'agit du fichier source principal de l'application qui contient la classe d'application CWSJTXHelperApp.

WSJTXHelper.rc
    Il s'agit de la liste de toutes les ressources Microsoft Windows utilisées par le programme. Il inclut les icônes, les bitmaps et les curseurs qui sont stockés dans le sous-répertoire RES. Ce fichier peut être directement modifié dans Microsoft Visual C++. Les ressources de votre projet se trouvent dans 1036.

res\WSJTXHelper.ico
    Il s'agit d'un fichier icône, qui est utilisé comme icône de l'application. Cette icône est incluse par le fichier de ressources principal WSJTXHelper.rc.

res\WSJTXHelper.rc2
    Ce fichier contient les ressources qui ne sont pas modifiées par Microsoft Visual C++. Vous devez placer toutes les ressources non modifiables par l'éditeur de ressources dans ce fichier.


/////////////////////////////////////////////////////////////////////////////

L'Assistant Application crée une classe de boîte de dialogue :

WSJTXHelperDlg.h, WSJTXHelperDlg.cpp - la boîte de dialogue
    Ces fichiers contiennent votre classe CWSJTXHelperDlg. Cette classe définit le comportement de la boîte de dialogue principale de votre application. Le modèle de la boîte de dialogue se trouve dans WSJTXHelper.rc, qui peut être modifié dans Microsoft Visual C++.

/////////////////////////////////////////////////////////////////////////////

Autres fichiers standard :

StdAfx.h, StdAfx.cpp
    Ces fichiers sont utilisés pour générer un fichier d'en-tête précompilé (PCH) WSJTXHelper.pch et un fichier de type précompilé nommé StdAfx.obj.

Resource.h
    Il s'agit du ficher d'en-tête standard, qui définit les nouveaux ID de ressources. Microsoft Visual C++ lit et met à jour ce fichier.

/////////////////////////////////////////////////////////////////////////////

Autres remarques :

L'Assistant Application utilise des commentaires "TODO:" pour indiquer les parties du code source où vous devrez ajouter ou modifier du code.

Si votre application utilise des MFC dans une DLL partagée, vous devez redistribuer les DLL MFC. Si la langue de votre application ne correspond pas aux paramètres régionaux du système d'exploitation, vous devrez également redistribuer les ressources localisées correspondantes mfc110XXX.DLL.
Pour plus d'informations sur ces deux rubriques, consultez la section sur la redistribution des applications Visual C++ dans la documentation MSDN.

/////////////////////////////////////////////////////////////////////////////
