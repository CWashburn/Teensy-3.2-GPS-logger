void rightISR(){

  if(isr_mode == SET_MODE || isr_mode == VAR_MODE || isr_mode == APP_MODE)
    cursorDown();  
  else if(isr_mode = EDIT_MODE){
    if(input_cursor < set_dig_dump[current_dump_index]-1)
      input_cursor++;
  }
}


void leftISR(){
  
  if(isr_mode == SET_MODE || isr_mode == VAR_MODE || isr_mode == APP_MODE)
    cursorUp();  

  else if(isr_mode = EDIT_MODE){
    if(input_cursor > 0)
      input_cursor--;
  }
}


void enterISR(){
  
  switch(isr_mode){

    case VAR_MODE:
      if(current_item_id % 16 == 0)
        launchVarBrowser(current_item_id);
      break;

    case SET_MODE:
      if(current_item_id % 16 == 0)
        launchSetBrowser(current_item_id);
      else
        editSet(); 

    case EDIT_MODE:
      drawSetItem(menu_index, set_title_dump[current_dump_index], set_ptr_dump[current_dump_index], set_unit_dump[current_dump_index]);

  }  
}


void upISR(){
  
  if(isr_mode == SET_MODE || isr_mode == VAR_MODE || isr_mode == APP_MODE)
    cursorUp(); 
  else if(EDIT_MODE)
    incInput();
}


void downISR(){

  if(isr_mode == SET_MODE || isr_mode == VAR_MODE || isr_mode == APP_MODE)
    cursorDown();
}



void cursorDown(){

  switch(isr_mode){

    case VAR_MODE:    

      if(menu_index == vis_menu_items-1){

        uint16_t next_id, index;
        uint16_t n = 1;       
         
        while((current_item_id/n) % 16 == 0)
          n *= 16;
        next_id = current_item_id + n;

        if(var_id_dump[current_dump_index+1] == next_id){
          current_dump_index++;
          current_id = next_id;
          var_id_buf[vis_menu_items-1] = var_id_dump[current_dump_index];
          var_title_buf[vis_menu_items-1] = var_title_dump[current_dump_index];
          var_ptr_buf[vis_menu_items-1] = var_ptr_buf[current_dump_index];          
        }

        else if(searchDump(var_id_dump, MAX_VARS, next_id, index){
          current_dump_index = index;
          current_id = next_id;
          var_id_buf[vis_menu_items-1] = var_id_dump[current_dump_index];
          var_title_buf[vis_menu_items-1] = var_title_dump[current_dump_index];
          var_ptr_buf[vis_menu_items-1] = var_ptr_buf[current_dump_index];
        }

        else
          return;          

        for(uint8_t i = 0; i < vis_menu_items-1; i++){      
          var_id_buf[i] =    var_id_buf[i+1];         
          var_title_buf[i] = var_title_buf[i+1];
          var_ptr_buf[i] =   var_ptr_buf[i+1];
          drawVarItem(i+min_vis_index, var_title_buf[i], var_ptr_buf[i]);
        }

        drawVarItem(cursor_index, var_title_buf[vis_menu_items-1], var_ptr_buf[vis_menu_items-1]);
      }

      else if(cursor_index < vis_menu_items-1){

        current_item_id = var_id_buf[cursor_index+1];
        drawVarItem(cursor_index, var_title_buf[cursor_index], var_ptr_buf[cursor_index]);
        cursor_index++;
        drawVarItem(cursor_index, var_title_buf[cursor_index], var_ptr_buf[cursor_index]);
      }

      break;


    case SET_MODE:    

      if(menu_index == vis_menu_items-1){

        uint16_t next_id, index;
        uint16_t n = 1;       
         
        while((current_item_id/n) % 16 == 0)
          n *= 16;
        next_id = current_item_id + n;

        if(set_id_dump[current_dump_index+1] == next_id){
          current_dump_index++;
          current_id = next_id;
          set_id_buf[vis_menu_items-1] = set_id_dump[current_dump_index];
          set_title_buf[vis_menu_items-1] = set_title_dump[current_dump_index];
          set_ptr_buf[vis_menu_items-1] = set_ptr_buf[current_dump_index];          
        }

        else if(searchDump(set_id_dump, MAX_SETS, next_id, index){
          current_dump_index = index;
          current_id = next_id;
          set_id_buf[vis_menu_items-1] = set_id_dump[current_dump_index];
          set_title_buf[vis_menu_items-1] = set_title_dump[current_dump_index];
          set_ptr_buf[vis_menu_items-1] = set_ptr_buf[current_dump_index];
        }

        else
          return;          

        for(uint8_t i = 0; i < vis_menu_items-1; i++){      
          set_id_buf[i] =    set_id_buf[i+1];         
          set_title_buf[i] = set_title_buf[i+1];
          set_ptr_buf[i] =   set_ptr_buf[i+1];
          drawSetItem(i+min_vis_index, set_title_buf[i], set_ptr_buf[i]);
        }

        drawSetItem(cursor_index, set_title_buf[vis_menu_items-1], set_ptr_buf[vis_menu_items-1]);
      }

      else if(cursor_index < vis_menu_items-1){

        current_item_id = set_id_buf[cursor_index+1];
        drawSetItem(cursor_index, set_title_buf[cursor_index], set_ptr_buf[cursor_index]);
        cursor_index++;
        drawSetItem(cursor_index, set_title_buf[cursor_index], set_ptr_buf[cursor_index]);
      }

      break;

    default:
  }
}






void cursorUp(){

  switch(isr_mode){
    
     case VAR_MODE:    

      if(menu_index == 0){

        uint16_t next_id, index;
        uint16_t n = 1;       
         
        while((current_item_id/n) % 16 == 0)
          n *= 16;
        next_id = current_item_id - n;

        if(var_id_dump[current_dump_index-1] == next_id){
          current_dump_index--;
          current_id = next_id;
          var_id_buf[0] = var_id_dump[current_dump_index];
          var_title_buf[0] = var_title_dump[current_dump_index];
          var_ptr_buf[0] = var_ptr_buf[current_dump_index];  
          drawVarItem(0, var_title_buf[0], var_ptr_buf[0]);        
        }

        else if(searchDump(var_id_dump, MAX_VARS, next_id, index){
          current_dump_index = index;
          current_id = next_id;
          var_id_buf[0] = var_id_dump[current_dump_index];
          var_title_buf[0] = var_title_dump[current_dump_index];
          var_ptr_buf[0] = var_ptr_buf[current_dump_index];  
          drawVarItem(0, var_title_buf[0], var_ptr_buf[0]);
        }

        else
          return;          

        for(uint8_t i = 1; i < vis_menu_items; i++){      
          var_id_buf[i+1] =    var_id_buf[i];         
          var_title_buf[i+1] = var_title_buf[i];
          var_ptr_buf[i+1] =   var_ptr_buf[i];
          drawVarItem(i+min_vis_index, var_title_buf[i], var_ptr_buf[i]);
        }        
      }

      else if(cursor_index < vis_menu_items){

        current_item_id = var_id_buf[cursor_index-1];
        drawVarItem(cursor_index, var_title_buf[cursor_index], var_ptr_buf[cursor_index]);
        cursor_index--;
        drawVarItem(cursor_index, var_title_buf[cursor_index], var_ptr_buf[cursor_index]);
      }

      break;

    case SET_MODE:    

      if(menu_index == 0){

        uint16_t next_id, index;
        uint16_t n = 1;       
         
        while((current_item_id/n) % 16 == 0)
          n *= 16;
        next_id = current_item_id - n;

        if(set_id_dump[current_dump_index-1] == next_id){
          current_dump_index--;
          current_id = next_id;
          set_id_buf[0] = set_id_dump[current_dump_index];
          set_title_buf[0] = set_title_dump[current_dump_index];
          set_ptr_buf[0] = set_ptr_buf[current_dump_index];  
          drawSetItem(0, set_title_buf[0], set_ptr_buf[0]);        
        }

        else if(searchDump(set_id_dump, MAX_SETS, next_id, index){
          current_dump_index = index;
          current_id = next_id;
          set_id_buf[0] = set_id_dump[current_dump_index];
          set_title_buf[0] = set_title_dump[current_dump_index];
          set_ptr_buf[0] = set_ptr_buf[current_dump_index];  
          drawSetItem(0, set_title_buf[0], set_ptr_buf[0]);
        }

        else
          return;          

        for(uint8_t i = 1; i < vis_menu_items; i++){      
          set_id_buf[i+1] =    set_id_buf[i];         
          set_title_buf[i+1] = set_title_buf[i];
          set_ptr_buf[i+1] =   set_ptr_buf[i];
          drawSetItem(i+min_vis_index, set_title_buf[i], set_ptr_buf[i]);
        }        
      }

      else if(cursor_index < vis_menu_items){

        current_item_id = set_id_buf[cursor_index-1];
        drawSetItem(cursor_index, set_title_buf[cursor_index], set_ptr_buf[cursor_index]);
        cursor_index--;
        drawSetItem(cursor_index, set_title_buf[cursor_index], set_ptr_buf[cursor_index]);
      }

      break;

    default:

  }
}

