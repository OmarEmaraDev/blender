# SPDX-FileCopyrightText: 2023 Blender Authors
#
# SPDX-License-Identifier: GPL-2.0-or-later

set(INC
  ../asset
  ../include
  ../../makesrna

  # RNA_prototypes.hh
  ${CMAKE_BINARY_DIR}/source/blender/makesrna
)

set(INC_SYS
)

set(SRC
  asset_catalog_tree_view.cc
  file_context.cc
  file_draw.cc
  file_indexer.cc
  file_ops.cc
  file_panels.cc
  file_utils.cc
  filelist/filelist.cc
  filelist/filelist_filter.cc
  filelist/filelist_sort.cc
  filesel.cc
  folder_history.cc
  fsmenu.cc
  fsmenu_system.cc
  space_file.cc

  file_indexer.hh
  file_intern.hh
  filelist.hh
  filelist/filelist_intern.hh
  fsmenu.h
)

set(LIB
  PRIVATE bf::asset_system
  PRIVATE bf::blenfont
  PRIVATE bf::blenkernel
  PRIVATE bf::blenlib
  PRIVATE bf::blenloader
  PRIVATE bf::blentranslation
  PRIVATE bf::dna
  PRIVATE bf::gpu
  PRIVATE bf::imbuf
  PRIVATE bf::imbuf::movie
  PRIVATE bf::intern::guardedalloc
  PRIVATE bf::extern::fmtlib
  PRIVATE bf::intern::atomic
  PRIVATE bf::render
  PRIVATE bf::windowmanager
)

if(WIN32)
  add_definitions(-DNOMINMAX)
  list(APPEND LIB
    PRIVATE bf::intern::utfconv
  )
endif()

if(WITH_HEADLESS)
  add_definitions(-DWITH_HEADLESS)
else()
  list(APPEND LIB
    bf_editor_datafiles
  )
endif()

if(WITH_IMAGE_OPENEXR)
  add_definitions(-DWITH_IMAGE_OPENEXR)
endif()

if(WITH_IMAGE_OPENJPEG)
  add_definitions(-DWITH_IMAGE_OPENJPEG)
endif()

if(WITH_IMAGE_CINEON)
  add_definitions(-DWITH_IMAGE_CINEON)
endif()

if(WITH_IMAGE_WEBP)
  add_definitions(-DWITH_IMAGE_WEBP)
endif()

if(WITH_FREESTYLE)
  add_definitions(-DWITH_FREESTYLE)
endif()

blender_add_lib(bf_editor_space_file "${SRC}" "${INC}" "${INC_SYS}" "${LIB}")

# RNA_prototypes.hh dna_type_offsets.h
add_dependencies(bf_editor_space_file bf_rna)
