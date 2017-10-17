# ClauToCpp
ToDo - Convert ClauText to CPP - Not yet..

# ClauText Code

      # Global
      # COUNT = 0

      # ROW_MAX = 0
      # COL_MAX = 0

      # Pos = { row = 1 col = 1 }
      # value = 1

    Main = { $call = { id = snail } }
      # int main(void) {
      #	snail();
      #	return 0;
      # }

    Event = {
      id = snail

      $call = { id = init row_max = 300 col_max = 300 }
        # _init(200, 200); // row_max, col_max ! but, in clautext, it can be to col_max, row_max

      #$print = { data = { chk } }
        # cout << "chk";

      ##$print2 = { data = { /./ } }
      #$print = { enter = { \n } }
        # cout << '\n';

      # $setElement = { dir = { $concat_all = { / . / Arr / $ ut1 } } idx = { 1 } val = { 1 } }
        # _setElement(_concat_all(vector<string>{"/", ".", "/", "Arr", "/", "$", "ut1"}), 1, 1);

      #$call = { id = print start_row = 1 start_col = 1 }
      #$print = { enter ={ \n } }

      # $call = { id = doing k = 0 }
        # _doing(0);

      ##$call = { id = print start_row = 1 start_col = 1 }
      #$_getch = { }
    }

    COUNT = 0

    ROW_MAX = 0
    COL_MAX = 0

    Pos = { row = 1 col = 1 }
    value = 1

    Event = {
      id = init

      $parameter = { row_max col_max }
        # inline string _init(const string& row_max, const string& col_max) {
        # 	~~
        # }

      $make = { dir = { $concat_all = { / . / Arr } } }
        # _make(_concat_all(vector<string>{"/", ".", "/", "Arr"}));

      $assign = { /./ROW_MAX value = { $parameter.row_max } }
        # _assign("/./ROW_MAX", _Find("$parameter.row_max"));

      $assign = { /./COL_MAX value = { $parameter.col_max } }
        # _assign("/./COL_MAX", _Find("$parameter.col_max"));

      $call = { id = init_Arr i = 0 }
        # _call("init_Arr", 0);
    }
    Event = {
      id = init_Arr

      $option = { REMOVE_IF_CALL_ONESELF_EVENT }

      $parameter = { i }
      $local = { i }

      $assign = { $local.i value = { $parameter.i } }

      $while = { 
        condition = { 
          $COMP<EQ = { $local.i $add = { 1 /./ROW_MAX } }
        }
        then = {
          $if = { 
            condition = {
              $OR = {
                $EQ = { 0 $local.i }
                $EQ = { $add = { 1 /./ROW_MAX } $local.i }
              }
            }
            then = {
              $make = { dirName = { $concat_all = {  / . / Arr / _ } } condition = { TRUE } }
              ##$call = { id = init_Arr2 row = $local.i i = 0 size = { $add = { 1 /./COL_MAX } } }
              $assign = { $local.i value = { $add = { 1 $local.i } } }
            }
          }
          $else = {
            then = {
              $make = { dirName = { $concat_all = {  / . / Arr / _ } } }
              $call = { id = init_Arr3 row = $local.i i = 0 size = { $add = { 1 /./COL_MAX } } }
              $assign = { $local.i value = { $add = { 1 $local.i } } }	
            }
          }
        }
      }
    }
    Event = {
      id = init_Arr2

      $option = { REMOVE_IF_CALL_ONESELF_EVENT }
      $parameter = { row i size }
      $local = { row i size }

      $assign = { $local.row value = { $parameter.row } }
      $assign = { $local.i value = { $parameter.i } }
      $assign = { $local.size value = { $parameter.size } }

      $while = { 
        condition = {
          $COMP<EQ = { $local.i $local.size }
        }
        then = {
          $insert = { dirName = { $concat_all = {  / . / Arr / $ ut $local.row  } } value = { -1 } }
          $assign = { $local.i value = { $add = { 1 $local.i } } }
        }
      }
    }
    Event = {
      id = init_Arr3

      $option = { REMOVE_IF_CALL_ONESELF_EVENT }
      $parameter = { row i size }
      $local = { row i size }

      $assign = { $local.row value = { $parameter.row } }
      $assign = { $local.i value = { $parameter.i } }
      $assign = { $local.size value = { $parameter.size } }

      $while = { 
        condition = {
          $COMP<EQ = { $local.i $local.size }
        }
        then = {
          $if = {
            condition = {
              $OR = {
                $EQ = { $local.i 0 }
                $EQ = { $local.i $add = { 1 /./COL_MAX } }
              }
            }
            then = {
              $insert = { dirName = { $concat_all = {  / . / Arr / $ ut $local.row  } } value = { -1 } }
              $assign = { $local.i value = { $add = { 1 $local.i } } }
            }
          }
          $else = {
            then = {
              $insert = { dirName = { $concat_all = {  / . / Arr / $ ut $local.row } } value = { 0 } }
              $assign = { $local.i value = { $add = { 1 $local.i } } }
            }
          }
        }
      }
    }

    Event = {
      id = doing

      $parameter = { k }
      $local = { x }

      $option = { REMOVE_IF_CALL_ONESELF_EVENT } 

      $assign = { $local.x val = { $parameter.k } }

      $if = { 
        condition = { $EQ = { $local.x 0 } }
        then = {
          $call = { id = canMoveRight }

          $if = {
            condition = {
              $return_value = { }
            }
            then = {
              $call = { id = moveRight }

              $assign2 = { dir = { $concat_all = { / . / value } } value = { $add = { 1 /./value } } }
              $setElement = { dir = { $concat_all = { / . / Arr / $ ut /Pos/row } } idx = { /Pos/col } value = { /./value } }


              $call = { id = doing k = $local.x }
            }
          }
          $else = {
            then = {
              $assign = { $local.x value = { 1 } }
            }
          }
        }
      }
      $if = { 
        condition = { $EQ = { 1 $local.x } } 
        then = { 
          $call = { id = canMoveDown }

          $if = {
            condition = {
              $return_value = { }
            }
            then = {
              $call = { id = moveDown }

              $assign2 = { dir = { $concat_all = { / . / value } } value = { $add = { 1 /./value } } }
              $setElement = { dir = { $concat_all = { / . / Arr / $ ut /Pos/row } } idx = { /Pos/col } value = { /./value } }
              $call = { id = doing k = $local.x }
            }
          }
          $else = {
            then = {
              $assign = { $local.x value = { 2 } }
            }
          }
        }
      }

      $if = { 
        condition = { $EQ = { 2 $local.x } } 
        then = { 
          $call = { id = canMoveLeft }

          $if = {
            condition = {
              $return_value = { }
            }
            then = {
              $call = { id = moveLeft }

              $assign2 = { dir = { $concat_all = { / . / value } } value = { $add = { 1 /./value } } }
              $setElement = { dir = { $concat_all = { / . / Arr / $ ut /Pos/row } } idx = { /Pos/col } value = { /./value } }
              $call = { id = doing k = $local.x }
            }
          }
          $else = {
            then = {
              $assign = { $local.x value = { 3 } }
            }
          }
        }
      }

      $if = { 
        condition = { $EQ = { 3 $local.x } } 
        then = { 
          $call = { id = canMoveUp }

          $if = {
            condition = {
              $return_value = { }
            }
            then = {
              $call = { id = moveUp }

              $assign2 = { dir = { $concat_all = { / . / value } } value = { $add = { 1 /./value } } }			
              $setElement = { dir = { $concat_all = { / . / Arr / $ ut /Pos/row } } idx = { /Pos/col } value = { /./value } }
              $call = { id = doing k = $local.x }
            }
          }
          $else = {
            then = {
              $assign = { $local.x value = { 0 } }

              $call = { id = canMoveRight }

              $if = {
                condition = {
                  $return_value = { }
                }
                then = {
                  $call = { id = doing k = $local.x }
                }
              }
              $else = {
                then = {
                  #
                }			
              }					
            }
          }
        }
      }

      $return = { }
    }

    Event = {
      id = print

      $option = { REMOVE_IF_CALL_ONESELF_EVENT }
      $parameter = { start_row start_col }

      $if = {
        condition = {
          $AND = {
            $COMP> = { $parameter.start_row /./ROW_MAX }
            $COMP>EQ = { $parameter.start_col /./COL_MAX }
          }
        }
        then = {
          $return = { }
        }
      }

      $if = {
        condition = {
          $COMP<EQ = { $parameter.start_col /./COL_MAX }
        }
        then = {
          $print = { data = { $element = { $concat_all = { / . / Arr / $ ut $parameter.start_row } $parameter.start_col } } }
          $print = { data = { " " } }
          $call = { id = print start_row = { $parameter.start_row } start_col = { $add = { 1 $parameter.start_col } } }
        }
      }
      $if = {
        condition = {
          $COMP< = { $parameter.start_row /./ROW_MAX }
        }
        then = {
          $print = { enter = { \n } }

          $call = { id = print start_row = { $add = { 1 $parameter.start_row } } start_col = 1 }
        }
      }
    }

    Event = {
      id = canMoveRight

      $if = {
        condition = {
          $AND_ALL = {
            $EQ = { 0 $element = { $concat_all = { / . / Arr / $ ut /./Pos/row } $add = { 1 /./Pos/col } } }
            #$AND = {
              $NOTEQ = { 0 $element = { $concat_all = { / . / Arr / $ ut $add = { -1 /./Pos/row }  } /./Pos/col } }
              #$NOTEQ = { 0 $element = { $concat_all = { / . / Arr / $ ut /./Pos/row ] } $add = { -1 /./Pos/col } } } 
            #}
          }
        }
        then = {
          $return = { TRUE }
        }
      }
      $return = { FALSE }
    }
    Event = {
      id = canMoveDown

      $if = {
        condition = {
          $AND_ALL = {
            $EQ = { 0 $element = { $concat_all = { /. / Arr / $ ut $add = { 1 /./Pos/row }  } /./Pos/col } }
            #$AND = {
              $NOTEQ = { 0 $element = { $concat_all = { /. / Arr / $ ut $add = { -1 /./Pos/row }  } /./Pos/col } }
              $NOTEQ = { 0 $element = { $concat_all = { /. / Arr / $ ut /./Pos/row } $add = { 1 /./Pos/col } } }
            #}
          }
        }
        then = {
          $return = { TRUE }
        }
      }
      $return = { FALSE }
    }
    Event = {
      id = canMoveLeft # and up

      $if = {
        condition = {
          #$AND = {
            $EQ = { 0 $element = { $concat_all = { /. / Arr  / $ ut $add = { -1 /./Pos/row } } $add = { -1 /./Pos/col } } }
            #$AND = {
            #	$NOTEQ = { 0 $element = { $concat_all = { /. / Arr / $ ut $add = { 1 /./Pos/row } } /./Pos/col } }
            #	$NOTEQ = { 0 $element = { $concat_all = { /. / Arr / $ ut /./Pos/row } $add = { 1 /./Pos/col } } }
            #}
          #}
        }
        then = {
          $return = { TRUE }
        }
      }
      $return = { FALSE }
    }
    Event = {
      id = canMoveUp

      $if = {
        condition = {
          $AND = {
            $EQ = { 0 $element = { $concat_all = { /. / Arr / $ ut  $add = { -1 /./Pos/row }  } /./Pos/col } }
            $AND = {
              $NOTEQ = { 0 $element = { $concat_all = { /. / Arr / $ ut $add = { 1 /./Pos/row }  } /./Pos/col } }
              $NOTEQ = { 0 $element = { $concat_all = { /. / Arr / $ ut /./Pos/row  } $add = { -1 /./Pos/col } } } 
            }
          }
        }
        then = {
          $return = { TRUE }
        }
      }
      $return = { FALSE }
    }

    Event = {
      id = moveRight

      $assign2 = { dir = { $concat_all = { / . / Pos / col } } value = { $add = { 1 /./Pos/col } } }
    }
    Event = {
      id = moveDown

      $assign2 = { dir = { $concat_all = { / . / Pos / row } } value = { $add = { 1 /./Pos/row } } }
    }
    Event = {
      id = moveLeft # and up

      $assign2 = { dir = { $concat_all = { / . / Pos / col } } value = { $add = { -1 /./Pos/col } } }
      $assign2 = { dir = { $concat_all = { / . / Pos / row } } value = { $add = { -1 /./Pos/row } } }
    }
    Event = {
      id = moveUp

      $assign2 = { dir = { $concat_all = { / . / Pos / row } } value = { $add = { -1 /./Pos/row } } }
    }
    #
#C++ Code
    

    // Goal : clautext -> cpp

    #define _CRT_SECURE_NO_WARNINGS
    #include <iostream>
    #include <string>
    #include <vector>
    #include <map>

    // no fast lib!
    #include <wiz/ClauText.h>

    #define INLINE inline

    wiz::StringBuilder builder(102400);

    INLINE std::string _add(const std::string& s1, const std::string& s2)
    {
      return std::to_string(std::stoi(s1) + std::stoi(s2)); // change to int, double, ..
    }
    INLINE bool _COMP_LT_EQ(const std::string& s1, const std::string& s2)
    {
      return wiz::load_data::Utility::Compare(s1, s2, &builder) == "< 0";
    }
    INLINE bool _OR(const bool x, const bool y)
    {
      return x || y;
    }
    INLINE bool _AND(const bool x, const bool y)
    {
      return x && y;
    }
    INLINE bool _EQ(const std::string& x, const std::string& y)
    {
      return x == y;
    }

    INLINE std::string _Find(wiz::load_data::UserType& global, const std::string& str) {
      return wiz::load_data::Find(&global, str, &builder);
    } 
    INLINE std::string _concat_all(const std::vector<std::string>& vec) // chk for -> no inline?
    {
      std::string result;

      for (int i = 0; i < vec.size(); ++i) {
        result += vec[i];
      }
      return result;
    }
    // todo - add ExcuteData parameter?
    INLINE std::string _make(wiz::load_data::UserType& global, const std::string& str, const std::string& condition)
    {
      std::string dir = str;

      dir = ToBool4(nullptr, global, dir, ExcuteData(), &builder);

      std::string name;
      for (int i = dir.size() - 1; i >= 0; --i)
      {
        if (dir[i] == '/') {
          name = wiz::String::substring(dir, i + 1);
          dir = wiz::String::substring(dir, 0, i - 1);
          break;
        }
      }
      if (dir.empty()) { dir = "."; }

      wiz::load_data::LoadData::AddUserType(global, dir, name, "", condition, ExcuteData(), &builder);

      return "";
    }
    INLINE std::string _assign(wiz::load_data::UserType& global, std::map<std::string, std::string>& locals, const std::string& dir, const std::string& value, const std::string& condition)
    {
      std::pair<std::string, std::string> _dir = Find2(&global, dir);

      //// todo!! - add locals to parameter.
      if (_dir.first == "" && wiz::String::startsWith(_dir.second, "$local."))
      {
        locals[wiz::String::substring(_dir.second, 7)] = value;
      }
      else 
      {
        wiz::load_data::LoadData::SetData(global, _dir.first, _dir.second, value, condition, ExcuteData(), &builder);
      }
      return "";
    }
    INLINE std::string _insert(wiz::load_data::UserType& global, const std::string& dir, const std::string& value, const std::string& condition)
    {
      wiz::load_data::LoadData::AddData(global, dir, value, condition, ExcuteData(), &builder);

      return "";
    }

    // user defined functions?
    INLINE std::string _snail(wiz::load_data::UserType* global);
    INLINE std::string _init(wiz::load_data::UserType* global, std::map<std::string, std::string>& parameters);
    INLINE std::string _init_Arr(wiz::load_data::UserType* global, std::map<std::string, std::string>& parameters);
    INLINE std::string _init_Arr3(wiz::load_data::UserType* global, std::map<std::string, std::string>& parameters);


    int main(void)
    {
      wiz::load_data::UserType global;
      std::string str = 
        "COUNT = 0 \
        ROW_MAX = 0 \
        COL_MAX = 0 \
        Pos = { row = 1 col = 1 } \
        value = 1";

      wiz::load_data::LoadData::LoadDataFromString(str, global);

      _snail(&global);

      //std::cout << global.ToString() << std::endl;

      return 0;
    }

    INLINE std::string _snail(wiz::load_data::UserType* global)
    {
      std::map<std::string, std::string> parameters1;

      parameters1["row_max"] = "300";
      parameters1["col_max"] = "300";

      _init(global, parameters1);

      //std::cout << "chk";
      //std::cout << "\n";

      // _setElement(global, _concat_all(std::vector<std::string>{"/", ".", "/", "Arr", "/", "$", "ut1"}), "1", "1");

      // _doing(global, 0);

      //GETCH(); // from wiz/ClauText.h?

      return "";
    }


    INLINE std::string _init(wiz::load_data::UserType* global, std::map<std::string, std::string>& parameters)
    {	
      std::map<std::string, std::string> locals;
      std::map<std::string, std::string> parameters1;

      _make(*global, _concat_all(std::vector<std::string>{"/", ".", "/", "Arr"}), "TRUE");
      _assign(*global, locals, "/./ROW_MAX", parameters["row_max"], "TRUE");
      _assign(*global, locals, "/./COL_MAX", parameters["col_max"], "TRUE");

      parameters1["i"] = "0";
      _init_Arr(global, parameters1);

      return "";
    }

    INLINE std::string _init_Arr(wiz::load_data::UserType* global, std::map<std::string, std::string>& parameters)
    {
      std::map<std::string, std::string> locals;

      locals["i"] = "";

      _assign(*global, locals, "$local.i", parameters["i"], "TRUE");

      while (_COMP_LT_EQ(locals["i"], _add("1", _Find(*global, "/./ROW_MAX"))))
      {
        if (_OR(_EQ("0", locals["i"]), _EQ(_add("1", _Find(*global, "/./ROW_MAX")), locals["i"])))
        {
          _make(*global, _concat_all(std::vector<std::string>{"/", ".", "/", "Arr", "/", "_"}), "TRUE");
          _assign(*global, locals, "$local.i", _add("1", locals["i"]), "TRUE");
        }
        else 
        {
          _make(*global, _concat_all(std::vector<std::string>{"/", ".", "/", "Arr", "/", "_"}), "TRUE");
          std::map<std::string, std::string> parameters1;
          parameters1["row"] = locals["i"];
          parameters1["i"] = "0";
          parameters1["size"] = _add("1", _Find(*global, "/./COL_MAX"));
          _init_Arr3(global, parameters1);
          _assign(*global, locals, "$local.i", _add("1", locals["i"]), "TRUE");
        }
      }

      return "";
    }

    INLINE std::string _init_Arr3(wiz::load_data::UserType* global, std::map<std::string, std::string>& parameters)
    {
      std::map<std::string, std::string> locals;

      locals["row"] = "";
      locals["i"] = "";
      locals["size"] = "";

      _assign(*global, locals, "$local.row", parameters["row"], "TRUE");
      _assign(*global, locals, "$local.i", parameters["i"], "TRUE");
      _assign(*global, locals, "$local.size", parameters["size"], "TRUE");

      while (_COMP_LT_EQ(locals["i"], locals["size"]))
      {
        if (_OR(_EQ(locals["i"], "0"), _EQ(locals["i"], _add("1", _Find(*global, "/./COL_MAX")))))
        {
          _insert(*global, _concat_all(std::vector<std::string>{"/", ".", "/", "Arr", "/", "$", "ut", locals["row"]}), "-1", "TRUE");
          _assign(*global, locals, "$local.i", _add("1", locals["i"]), "TRUE");
        }
        else
        {
          _insert(*global, _concat_all(
            std::vector<std::string>{"/", ".", "/", "Arr", "/", "$", "ut", locals["row"]}
          ), "0", "TRUE");
          _assign(*global, locals, "$local.i", _add("1", locals["i"]), "TRUE");
        }
      }

      return "";
    }


