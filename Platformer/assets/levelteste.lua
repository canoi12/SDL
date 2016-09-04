return {
  version = "1.1",
  luaversion = "5.1",
  tiledversion = "0.17.0",
  orientation = "orthogonal",
  renderorder = "right-down",
  width = 24,
  height = 24,
  tilewidth = 16,
  tileheight = 16,
  nextobjectid = 28,
  properties = {},
  tilesets = {
    {
      name = "ground",
      firstgid = 1,
      tilewidth = 16,
      tileheight = 16,
      spacing = 0,
      margin = 0,
      image = "../../../love2d/365indiesJam/Assets/ground.png",
      imagewidth = 112,
      imageheight = 64,
      tileoffset = {
        x = 0,
        y = 0
      },
      properties = {},
      terrains = {},
      tilecount = 28,
      tiles = {
        {
          id = 0,
          properties = {
            ["solid"] = 1
          }
        },
        {
          id = 2,
          properties = {
            ["solid"] = 1
          }
        },
        {
          id = 3,
          properties = {
            ["solid"] = 1
          }
        },
        {
          id = 5,
          properties = {
            ["solid"] = 1
          }
        },
        {
          id = 10,
          properties = {
            ["solid"] = 1
          }
        },
        {
          id = 11,
          properties = {
            ["solid"] = 1
          }
        },
        {
          id = 12,
          properties = {
            ["solid"] = 1
          }
        },
        {
          id = 13,
          properties = {
            ["solid"] = 1
          }
        },
        {
          id = 17,
          properties = {
            ["solid"] = 1
          }
        },
        {
          id = 18,
          properties = {
            ["solid"] = 1
          }
        },
        {
          id = 19,
          properties = {
            ["solid"] = 1
          }
        },
        {
          id = 21,
          properties = {
            ["solid"] = 1
          }
        },
        {
          id = 25,
          properties = {
            ["solid"] = 1
          }
        },
        {
          id = 26,
          properties = {
            ["solid"] = 1
          }
        },
        {
          id = 27,
          properties = {
            ["solid"] = 1
          }
        }
      }
    }
  },
  layers = {
    {
      type = "tilelayer",
      name = "Camada de Tiles 1",
      x = 0,
      y = 0,
      width = 24,
      height = 24,
      visible = true,
      opacity = 1,
      offsetx = 0,
      offsety = 0,
      properties = {},
      encoding = "lua",
      data = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12,
        1, 1, 1, 1, 1, 1, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12,
        3, 3, 3, 3, 3, 3, 3, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 0, 0, 0, 13, 21,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 11, 0, 0, 0, 0, 12,
        22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 3, 3, 3, 28, 0, 0, 13, 19, 21,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 3, 11, 0, 0, 0, 0, 0, 12,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 3, 25, 19, 20, 0, 0, 0, 12,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 3, 11, 0, 0, 0, 0, 0, 12,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 3, 11, 0, 0, 0, 13, 19, 21,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 3, 25, 19, 20, 0, 0, 0, 12,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 3, 11, 0, 0, 0, 0, 0, 12,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 3, 5, 1, 1, 4, 0, 0, 12,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 26, 22, 22, 22, 22, 28, 0, 0, 12,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 21,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12,
        1, 1, 1, 1, 1, 1, 1, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 1, 1, 7,
        3, 3, 3, 3, 3, 3, 3, 3, 11, 0, 27, 0, 27, 0, 6, 1, 1, 1, 1, 1, 7, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 11, 0, 0, 0, 0, 0, 12, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 11, 0, 0, 0, 0, 0, 12, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 11, 0, 0, 0, 0, 0, 12, 3, 3, 3, 3, 3, 3, 3, 3, 3
      }
    },
    {
      type = "objectgroup",
      name = "Camada de Objetos 1",
      visible = true,
      opacity = 1,
      offsetx = 0,
      offsety = 0,
      draworder = "topdown",
      properties = {},
      objects = {
        {
          id = 14,
          name = "Dolphin",
          type = "Enemy",
          shape = "rectangle",
          x = 191,
          y = 52,
          width = 16,
          height = 16,
          rotation = 0,
          gid = 8,
          visible = true,
          properties = {}
        }
      }
    },
    {
      type = "objectgroup",
      name = "Camada de Objetos 2",
      visible = true,
      opacity = 1,
      offsetx = 0,
      offsety = 0,
      draworder = "topdown",
      properties = {},
      objects = {
        {
          id = 17,
          name = "",
          type = "",
          shape = "rectangle",
          x = 0,
          y = 0,
          width = 128,
          height = 128,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 18,
          name = "",
          type = "",
          shape = "rectangle",
          x = 0,
          y = 128,
          width = 128,
          height = 128,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 19,
          name = "",
          type = "",
          shape = "rectangle",
          x = 256,
          y = 0,
          width = 128,
          height = 128,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 20,
          name = "",
          type = "",
          shape = "rectangle",
          x = 256,
          y = 256,
          width = 128,
          height = 128,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 23,
          name = "",
          type = "",
          shape = "rectangle",
          x = 128,
          y = 256,
          width = 128,
          height = 128,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 24,
          name = "",
          type = "",
          shape = "rectangle",
          x = 0,
          y = 256,
          width = 128,
          height = 128,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 25,
          name = "",
          type = "",
          shape = "rectangle",
          x = 128,
          y = 0,
          width = 128,
          height = 128,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 26,
          name = "",
          type = "",
          shape = "rectangle",
          x = 256,
          y = 128,
          width = 128,
          height = 128,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 27,
          name = "",
          type = "",
          shape = "rectangle",
          x = 128,
          y = 128,
          width = 128,
          height = 128,
          rotation = 0,
          visible = true,
          properties = {}
        }
      }
    }
  }
}
