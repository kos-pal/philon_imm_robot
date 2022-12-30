import tkinter as tk
import global_vars
import funct
import os


#set global vars to 0 for debugging
#global_vars.imm_signals = 0
#global_vars.imm_relays = 0
#global_vars.servo_errors = 0
#global_vars.servo_status = 0
#global_vars.x_position = 0
#global_vars.y_position = 0
#global_vars.z_position = 0
#global_vars.servo_mode = 0
#global_vars.z_mod_inputs = 0
#global_vars.z_mod_outputs = 0





def update_ui():
    root.update()
    

# this is called before the while 1 loop for debugging
def update_whole_ui():
    update_ui_var("IMM_INPUTS")
    update_ui_var("IMM_OUTPUTS")
    update_ui_var("SERVO_ERRORS")
    #update_ui_var("SERVO_STATUS")
    update_ui_var("ZMOD_INPUTS")
    update_ui_var("ZMOD_OUTPUTS")
    set_position_labels(1)
    set_position_labels(2)
    set_position_labels(3)
    change_mode(global_vars.servo_mode, 0)
    #change_ignore_phys_switch()


def toggle_fullscreen():
    if toggle_fullscreen.flag == 0:
        root.attributes("-fullscreen",True)
        toggle_fullscreen.flag = 1
    else:
        root.attributes("-fullscreen",False)
        toggle_fullscreen.flag = 0
        
toggle_fullscreen.flag=0


def set_position_labels(axis):
    if axis == 1:
        pos_text = "X Position\n" + str(global_vars.x_position)
        x_pos_label.config(text=pos_text)
    elif axis == 2:
        pos_text = "Y Position\n" + str(global_vars.y_position)
        y_pos_label.config(text=pos_text)
    elif axis == 3:
        pos_text = "Z Position\n" + str(global_vars.z_position)
        z_pos_label.config(text=pos_text)


def update_item_stats():
    cycles_completed_label.config(
        text="Cycles completed\n"+str(global_vars.cycles)
    )
    items_completed_label.config(
        text="Items completed\n"+str(global_vars.items_completed)
    )
    items_discarded_su_label.config(
        text="Items discarded (Startup)\n"+str(global_vars.items_discarded)
    )
    items_discarded_qc_label.config(
        text="Items for Quality Control\n"+str(global_vars.items_for_qc)
    )


def change_ui_buttons_state(frame, offset, state):
    widgs = frame.winfo_children()[offset].winfo_children()
    for i in widgs:
        i.winfo_children()[0].config(state=state)


def change_ignore_phys_switch():
    if global_vars.ignore_physical_switch == 0:
        # disable physical switch
        global_vars.ignore_physical_switch = 1
        ignore_phys_switch_button.config(
            bg="#00BA00"
        )
        #enable mode switch buttons
        manual_button.config(state="active")
        auto_button.config(state="active")




    else:
        # enable physical switch
        global_vars.ignore_physical_switch = 0
        ignore_phys_switch_button.config(
            bg="#F0F0F0"
        )
        # disable mode switch buttons
        manual_button.config(state="disabled")
        auto_button.config(state="disabled")


    print("ingore_physical_switch :" + str(global_vars.ignore_physical_switch))


def change_mode(mode, set_flag):
    if set_flag == 1:
        #setting the servo mode
        if funct.set_servo_mode(mode) == 1:
            print("error setting servo mode")
            return
    # update the buttons either way
    if mode == 0:
        manual_button.config(image=manual_image)
        auto_button.config(image=auto_dis_image)
        auto_mode_frame.grid_forget()
        manual_position_frame.grid(row=0, column=0)
        # re-enable PROGRAM and Change program buttons
        prog_button.config(state="active")
        prgm_sel_fram_children = program_select_frame.winfo_children()
        if len(prgm_sel_fram_children) > 0:
            if prgm_sel_fram_children[len(prgm_sel_fram_children) - 1].winfo_class() == "Button":
                prgm_sel_fram_children[len(prgm_sel_fram_children) - 1].config(state="active")
            else:
                print("last widget is not a button")
        # re-enable ui outputs buttons
        change_ui_buttons_state(frame_imm, 1, "active")
        change_ui_buttons_state(frame_zmod, 1, "active")
    elif mode == 1:
        auto_button.config(image=auto_image)
        manual_button.config(image=manual_dis_image)
        manual_position_frame.grid_forget()
        auto_mode_frame.grid(row=0, column=0)
        auto_mode_frame.config(
            highlightbackground="grey",
            highlightthickness=2
        )
        #disable PROGRAM and Change program buttons
        prog_button.config(state="disabled")
        prgm_sel_fram_children = program_select_frame.winfo_children()
        if len(prgm_sel_fram_children) > 0:
            if prgm_sel_fram_children[len(prgm_sel_fram_children)-1].winfo_class() == "Button":
                prgm_sel_fram_children[len(prgm_sel_fram_children) - 1].config(state="disabled")
            else:
                print("last widget is not a button")
        #disable ui outputs buttons
        change_ui_buttons_state(frame_imm, 1, "disabled")
        change_ui_buttons_state(frame_zmod, 1, "disabled")

    elif mode == 2:
        auto_button.config(image=auto_dis_image)
        manual_button.config(image=manual_dis_image)
        auto_mode_frame.grid_forget()
        manual_position_frame.grid(row=0, column=0)
        # disable PROGRAM and Change program buttons
        prog_button.config(state="disabled")
        prgm_sel_fram_children = program_select_frame.winfo_children()
        if len(prgm_sel_fram_children) > 0:
            if prgm_sel_fram_children[len(prgm_sel_fram_children) - 1].winfo_class() == "Button":
                prgm_sel_fram_children[len(prgm_sel_fram_children) - 1].config(state="disabled")
            else:
                print("last widget is not a button")
        # re-enable ui outputs buttons
        change_ui_buttons_state(frame_imm, 1, "active")
        change_ui_buttons_state(frame_zmod, 1, "active")


def click_negative(event, button):
    if button == 0:
        message = "2.3.1.0." + str(manual_speed.get())
        print(message)
    elif button == 1:
        message = "2.3.2.0." + str(manual_speed.get())
        print(message)
    elif button == 2:
        message = "2.3.3.0." + str(manual_speed.get())
        print(message)
    #funct.append_and_send(message,20)
    funct.append_message(message)

def click_positive(event, button):
    if button == 0:
        message = "2.3.1.1000." + str(manual_speed.get())
        print(message)
    elif button == 1:
        message = "2.3.2.300." + str(manual_speed.get())
        print(message)
    elif button == 2:
        message = "2.3.3.740." + str(manual_speed.get())
        print(message)
    #funct.append_and_send(message,20)
    funct.append_message(message)


def released_manual_move(event, button):
    if button == 0:
        message = "2.7"
        print(message)
    elif button == 1:
        message = "2.7"
        print(message)
    elif button == 2:
        message = "2.7"
        print(message)
    else:
        return
    #funct.append_and_send(message,20)
    funct.append_message(message)

def servo_move(move_mode):
    try:
        x_requested = int(coord_text[0].get())
    except:
        coord_text[0].set("Invalid")
        return
    try:
        y_requested = int(coord_text[1].get())
    except:
        coord_text[1].set("Invalid")
        return
    try:
        z_requested = int(coord_text[2].get())
    except:
        coord_text[2].set("Invalid")
        return
    axes_speed = manual_speed.get()
    print("Sending Move " + str(x_requested) + "." + str(y_requested) + "." + str(z_requested) + "." + str(
        axes_speed) + "." + str(axes_speed) + "." + str(axes_speed))
    if move_mode == 0 :
        #move x,y,z
        funct.move_to_position(x_requested,y_requested,z_requested,axes_speed,axes_speed,axes_speed)
    elif move_mode == 1:
        #safe move x,y,z
        funct.move_to_position_safe(x_requested,y_requested,z_requested,axes_speed,axes_speed,axes_speed)
        

def change_prg_string(var, button):
    if var == "IMM_INPUTS":
        var_len = 7
    elif var == "IMM_OUTPUTS":
        var_len = 8
    elif var == "ZMOD_INPUTS":
        var_len = 3
    elif var == "ZMOD_OUTPUTS":
        var_len = 3
    button_index = var_len - 1 - button
    child = prgm_config_frame.winfo_children()[0].winfo_children()[button_index].winfo_children()[0]
    if prg_char_value[button_index] == '*':
        prg_char_value[button_index] = '0'
        child.config(image=false_image)
    elif prg_char_value[button_index] == '0':
        prg_char_value[button_index] = '1'
        child.config(image=true_image)
    elif prg_char_value[button_index] == '1':
        prg_char_value[button_index] = '*'
        child.config(image=not_updated_image)


def destroy_widg_children(widg, start_index):
    for child in widg.winfo_children()[start_index:]:
        child.destroy()


def set_ui_outputs(var, index):
    format_type = ''
    if var == "IMM_OUTPUTS":
        var = global_vars.imm_relays
        message = "1.1."
        master_frame = frame_imm
        children_offset = 1
        format_type = '08b'    
    elif var == "ZMOD_OUTPUTS":
        var = global_vars.z_mod_outputs
        message = "3.1."
        master_frame = frame_zmod
        children_offset = 1
        format_type = '03b'
    if (var >> index) & 1 == 1:
        var &= ~(1 << index)
    else:
        var |= (1 << index)
    message += format(var, format_type)
    #message += str(bin(var))[2:]
    #print(message)
    # set image to not updated
    widgs = master_frame.winfo_children()[children_offset].winfo_children()
    widgs[(len(widgs) - 1) - index].winfo_children()[0].config(image=not_updated_image)
    #print(message)
    #funct.append_and_send(message,20)
    funct.append_message(message)
    
    
def update_ui_var(var):
    if var == "IMM_INPUTS":
        var = global_vars.imm_signals
        var_len = 7
        master_frame = frame_imm
        children_offset = 0
        #print("imm in")
    elif var == "IMM_OUTPUTS":
        var = global_vars.imm_relays
        var_len = 8
        master_frame = frame_imm
        children_offset = 1
        #print("imm out")
    elif var == "SERVO_ERRORS":
        #var = global_vars.servo_errors
        #revert servo_errors
        var = ~global_vars.servo_errors&0xFF
        var_len = 8
        master_frame = frame_servo
        children_offset = 0
        #print("servo errors")
    elif var == "SERVO_STATUS":
        var = global_vars.servo_status
        var_len = 16
        master_frame = frame_servo
        children_offset = 1
        #print("servo status")
    elif var == "ZMOD_INPUTS":
        var = global_vars.z_mod_inputs
        var_len = 3
        master_frame = frame_zmod
        children_offset = 0
        #print("zmod in "+str(bin(global_vars.z_mod_inputs)))
    elif var == "ZMOD_OUTPUTS":
        var = global_vars.z_mod_outputs
        var_len = 3
        master_frame = frame_zmod
        children_offset = 1
        #print("imm out")
        
    widgs = master_frame.winfo_children()[children_offset].winfo_children()
    #print("var is : "+str(bin(var)))
    for i in range(var_len):
        if (var >> ((var_len - 1) - i)) & 1 == 1:
            widgs[i].winfo_children()[0].config(image=true_image)
        else:
            widgs[i].winfo_children()[0].config(image=false_image)


def check_if_folder_exists(folder):
    avail_programs = os.listdir(global_vars.folder_path+"saved_programs")
    for i in avail_programs:
        if i == folder:
            return 0
    return 1


def set_selected_program(folder):
    f = open(global_vars.folder_path+"robot_config.txt","r")
    config_lines= f.readlines()
    if len(config_lines)>0:
        config_lines[0]=folder+"\n"
        f.close()
    else:
        config_lines.append(folder+"\n")
    f = open(global_vars.folder_path+"robot_config.txt","w")
    for i in config_lines:
        f.write(i)
    f.close()
    #parse the config file again
    funct.parse_config_file()
    #reset the menu
    create_program_selection_widgets(0)
    #set raspberry to programing state to reprogram the servo arduino
    global_vars.raspb_state = "PROGRAM"


def create_program_selection_widgets(operation):
    destroy_widg_children(program_select_frame, 1)
    avail_programs = os.listdir(global_vars.folder_path+"saved_programs")
    programs_found = len(avail_programs)
    global selected_program
    selected_found = "None"
    not_selected_programs = []
    for i in range(programs_found):
        if avail_programs[i] == global_vars.selected_program:
            selected_found = avail_programs[i]
        else:
            not_selected_programs.append(avail_programs[i])

    if operation == 0:
        print(global_vars.selected_program)
        # show selected and available programs
        selected_prog_label = tk.Label(
            master=program_select_frame,
            font=("TkDefaultFont", 10)
        )
        selected_prog_label.grid(row=1, column=0, pady=(5, 5))
        avail_progs_label = tk.Label(
            master=program_select_frame,
            font=("TkDefaultFont", 10)
        )
        avail_progs_label.grid(row=2, column=0, pady=(5, 5))

        selected_prog_label.config(
            text="Selected program\n"+selected_found
        )
        if len(not_selected_programs) > 0:
            avail_progs_text = "Available programs\n"
            for i in not_selected_programs:
                avail_progs_text += i + "\n"
            avail_progs_label.config(
                text=avail_progs_text
            )
            change_prog_button = tk.Button(
                master=program_select_frame,
                text="Change program",
                command=lambda m=1:create_program_selection_widgets(m)
            )
            change_prog_button.grid(row=3, column=0)
        else:
            if selected_found == "None":
                selected_prog_label.grid_forget()
                avail_progs_label.config(
                    text="No programs available"
                )
    if operation == 1:
        #change program menu
        avail_progs_label = tk.Label(
            master=program_select_frame,
            text="Available programs",
            font=("TkDefaultFont", 10)
        )
        avail_progs_label.grid(row=1, column=0, pady=(5, 5))
        for i in range(len(not_selected_programs)):
            widg=tk.Button(
                master=program_select_frame,
                text=not_selected_programs[i],
                font=("TkDefaultFont", 10),
                command=lambda m=not_selected_programs[i]:set_selected_program(m)
            )
            widg.grid(row=2+i, column=0)


def create_widgets(var, master, type, function, column_num, row, column):
    var_frame = tk.Frame(
        master=master
    )
    var_frame.grid(row=row, column=column)
    frames_per_column = (len(var) / column_num)
    var_len = len(var)
    for i in range(var_len):
        widg_frame = tk.Frame(
            master=var_frame
        )

        widg_frame.grid(row=int(i % frames_per_column), column=int(i / frames_per_column), sticky=tk.W)
        if type == "OUTPUT":
            if var == imm_inputs:
                linked_var = "IMM_INPUTS"
                if i == 1 or i == 6:
                    #do not show automatic and emergenct stop options
                    continue
            elif var == imm_outputs:
                linked_var = "IMM_OUTPUTS"
                try:
                    selection = prog_list.curselection()[0]
                    if (selection == 1) and (i == 0 or i == 4 or i == 5) :
                        #do not show these options
                        continue
                except Exception:
                    pass
            elif var == zmod_inputs:
                linked_var = "ZMOD_INPUTS"
            elif var == zmod_outputs:
                linked_var = "ZMOD_OUTPUTS"
            widg = tk.Button(
                master=widg_frame,
                image=not_updated_image
            )
            if function != "NONE":
                widg.config(command=lambda m=linked_var, z=(var_len - 1) - i: function(m, z))

        else:
            widg = tk.Label(
                master=widg_frame,
                image=not_updated_image
            )

        widg.pack(side=tk.LEFT)
        widg = tk.Label(
            master=widg_frame,
            text=var[i]
        )
        widg.pack(side=tk.LEFT)


def swap_prg_moving_axes(index, dir):
    temp = prg_moving_axes[index]
    prg_moving_axes[index] = prg_moving_axes[index + 1 - (2 * dir)]
    prg_moving_axes[index + 1 - (2 * dir)] = temp

    # rerun configure_move to change display order
    configure_move(0, 0)


def lock_move_order():
    list_len = len(prg_moving_axes)

    # destroy the Confirm order button
    destroy_widg_children(prgm_config_frame, list_len)

    if list_len == 1:
        # no buttons to remove, return
        # enable axis button
        prgm_config_frame.winfo_children()[0].winfo_children()[0].config(state="active")
        config_label.config(
            text="Configure the move,\n"
                 "then click confirm"
        )
    else:
        for i in range(list_len):
            axis_frame = prgm_config_frame.winfo_children()[i]
            destroy_widg_children(axis_frame, 1)
            axis_frame.winfo_children()[0].config(state="active")

    config_label.config(
        text="Configure each axis\n"
             "move, then click confirm"
    )


def confirm_axis_move(axis):
    axis_button_index = prg_moving_axes.index(axis)
    # print(str(axis_button_index))
    # print(prgm_config_frame.winfo_children()[axis_button_index].winfo_class())

    prgm_config_frame.winfo_children()[axis_button_index].winfo_children()[0].config(
        bg="#00BA00",
        state="disabled"
    )

    list_len = len(prg_moving_axes)
    destroy_widg_children(prgm_config_frame, list_len)

    # check if all the buttons have been disabled

    disabled_buttons = 0
    for i in range(list_len):
        if prgm_config_frame.winfo_children()[i].winfo_children()[0].cget("state") == "disabled":
            disabled_buttons += 1
    if disabled_buttons == list_len:
        print("all axis confirmed")
        # re-enable save command button
        prog_button.config(state="active")

        # change text of config_label and destroy all other widgets
        config_label.config(
            text="Move configure properly\n"
                 "Select Save command to record it"
        )
        destroy_widg_children(prgm_config_frame, 0)
        # create a new empty label just to resize prgm_config_frame
        empty_label = tk.Label(
            master=prgm_config_frame,
            text=""
        )
        empty_label.grid(row=0, column=0)


def configure_move(operation, axis):
    if operation == 0:
        prev_x = prev_position[0]
        prev_y = prev_position[1]
        prev_z = prev_position[2]
        if len(prg_moving_axes) == 0:
            if global_vars.x_position != prev_x:
                # print("x change")
                prg_moving_axes.append("X")
            if global_vars.y_position != prev_y:
                # print("y change")
                prg_moving_axes.append("Y")
            if global_vars.z_position != prev_z:
                # print("z change")
                prg_moving_axes.append("Z")

        # hide previous widg if there
        destroy_widg_children(prgm_config_frame, 0)

        if len(prg_moving_axes) == 0:
            config_label.config(
                text="Robot is at the same spot\n"
                     "Move robot to the desired\n"
                     "start position and click\n"
                     "Configure move"
            )
        else:
            if len(prg_moving_axes) > 1:
                config_label.config(
                    text="Order the sequence in\n"
                         "which the axes should\n"
                         "move, then click confirm order"
                )
                for i in range(len(prg_moving_axes)):
                    axis_frame = tk.Frame(
                        master=prgm_config_frame
                    )
                    axis_frame.grid(row=i, column=0)
                    widg = tk.Button(
                        master=axis_frame,
                        text=prg_moving_axes[i],
                        state="disabled",
                        command=lambda m=1, a=prg_moving_axes[i]: configure_move(m, a)
                    )
                    widg.grid(row=0, column=0, rowspan=2)
                    # create buttons to swap positions
                    if i == 0 and len(prg_moving_axes) > 1:
                        widg = tk.Button(
                            master=axis_frame,
                            image=arrow_down,
                            command=lambda index=i, dir=0: swap_prg_moving_axes(index, dir)
                        )
                        widg.grid(row=1, column=1)
                    elif i == (len(prg_moving_axes) - 1) and len(prg_moving_axes) > 1:
                        widg = tk.Button(
                            master=axis_frame,
                            image=arrow_up,
                            command=lambda index=i, dir=1: swap_prg_moving_axes(index, dir)
                        )
                        widg.grid(row=0, column=1)
                    elif len(prg_moving_axes) != 1:
                        widg = tk.Button(
                            master=axis_frame,
                            image=arrow_up,
                            command=lambda index=i, dir=1: swap_prg_moving_axes(index, dir)
                        )
                        widg.grid(row=0, column=1)
                        widg = tk.Button(
                            master=axis_frame,
                            image=arrow_down,
                            command=lambda index=i, dir=0: swap_prg_moving_axes(index, dir)
                        )
                        widg.grid(row=1, column=1)

                widg = tk.Button(
                    master=prgm_config_frame,
                    text="Confirm order",
                    command=lock_move_order
                )
                widg.grid(row=3, column=0)

            else:
                # single axis change
                axis_frame = tk.Frame(
                    master=prgm_config_frame
                )
                axis_frame.grid(row=0, column=0)
                widg = tk.Button(
                    master=axis_frame,
                    text=prg_moving_axes[0],
                    state="active",
                    command=lambda m=1, a=prg_moving_axes[0]: configure_move(m, a)
                )
                widg.grid(row=0, column=0, rowspan=2)

        # print(prg_moving_axes)
    elif operation == 1:
        # delete any previous widgets
        prgm_conf_fr_ch = prgm_config_frame.winfo_children()
        child_num = len(prgm_conf_fr_ch)

        if child_num > 4:
            for child in prgm_conf_fr_ch[4:]:
                child.destroy()

        if axis == "X":
            # print("X AXIS")
            vars_index = 0
            current_pos = global_vars.x_position
        elif axis == "Y":
            # print("Y AXIS")
            vars_index = 1
            current_pos = global_vars.y_position
        else:
            # print("Z AXIS")
            vars_index = 2
            current_pos = global_vars.z_position

        prev_pos = prev_position[vars_index]

        widg = tk.Label(
            master=prgm_config_frame,
            text=axis + " axis configuration",
            font=("TkDefaultFont", 10)
        )
        widg.grid(row=4, column=0, pady=(5, 0))

        widg = tk.Scale(
            master=prgm_config_frame,
            label="Move speed",
            from_=1,
            to=100,
            orient="horizontal",
            variable=prgm_speed_vars[vars_index]
        )
        widg.grid(row=5, column=0)

        if prg_moving_axes.index(axis) != len(prg_moving_axes) - 1:
            # print("not last axis")
            widg = tk.Label(
                master=prgm_config_frame,
                text="Select at which point of moving\nshould the next axis start"
            )
            widg.grid(row=6, column=0)
            widg = tk.Scale(
                master=prgm_config_frame,
                from_=prev_pos,
                to=current_pos,
                orient="horizontal",
                variable=prgm_mm_delay_vars[vars_index]
            )
            widg.grid(row=7, column=0)
            widg.set(prev_pos)
        else:
            # this is the last axis of the move, set delay to 1201
            prgm_mm_delay_vars[vars_index].set(1201)

        widg = tk.Button(
            master=prgm_config_frame,
            text="Confirm",
            command=lambda m=axis: confirm_axis_move(m)
        )
        widg.grid(row=8, column=0)


# called when user selects options from prog_list Listbox
def list_change(event):
    if len(event.widget.curselection()) > 0:
        selection = event.widget.curselection()[0]
    else:
        #something outside the list was selected, ignore
        return
    destroy_widg_children(prgm_config_frame, 0)

    config_label.grid(row=2, column=0, pady=(5, 5))
    prgm_config_frame.grid(row=3, column=0)
    #reset prg_char_value
    for i in range(len(prg_char_value)):
        prg_char_value[i] = '*'

    # enable prog_button in case it was disabled
    prog_button.config(state="active")

    if selection == 0:
        config_label.config(
            text="Robot will wait until "
                 "signals from IMM "
                 "match the following"
        )
        # reset prg_char_value to all  *
        for i in range(7):
            prg_char_value[i] = '*'    
        create_widgets(imm_inputs, prgm_config_frame, "OUTPUT", change_prg_string, 1, 0, 0)

    elif selection == 1:
        config_label.config(
            text="Robot will set the "
                 "following IMM relays"
        )
        # reset prg_char_value to all  *
        for i in range(8):
            prg_char_value[i] = '*'

        create_widgets(imm_outputs, prgm_config_frame, "OUTPUT", change_prg_string, 1, 0, 0)

    elif selection == 2:
        config_label.config(
            text="Robot will wait until "
                 "signals from Zmod "
                 "match the following"
        )
        create_widgets(zmod_inputs, prgm_config_frame, "OUTPUT", change_prg_string, 1, 0, 0)

    elif selection == 3:
        config_label.config(
            text="Robot will set the "
                 "following Zmod relays "
        )
        create_widgets(zmod_outputs, prgm_config_frame, "OUTPUT", change_prg_string, 1, 0, 0)

    elif selection == 4:
        prog_button.config(state="disabled")

        # reset global_vars.prg_moving_axes if there were any items in list
        if len(prg_moving_axes) > 0:
            prg_moving_axes.clear()

        config_label.config(
            text="Move robot to the "
                 "required position "
                 "and hit Configure move "
        )

        widg = tk.Button(
            master=prgm_config_frame,
            text="Configure move",
            command=lambda m=0, a="": configure_move(m, a)
        )
        widg.grid(row=0, column=0)
    elif selection == 5:

        # enable prog_button in case it was disabled
        prog_button.config(state="active")

        config_label.config(
            text="Delays the robot "
                 "Select the required "
                 "miliseconds"
        )

        widg = tk.Entry(
            master=prgm_config_frame,
            exportselection=0
        )
        widg.grid(row=0, column=0)

    elif selection == 6:

        # enable prog_button in case it was disabled
        prog_button.config(state="active")

        config_label.config(
            text="The robot will "
                 "discard the selected "
                 "number of items at "
                 "startup during this point "
                 "and it will revert to "
                 "the start of the cycle\n"
                 "Move robot to the "
                 "position that you wish "
                 "to discard at,select "
                 "how many should be "
                 "discarded and hit "
                 "Save command"
        )

        widg = tk.Entry(
            master=prgm_config_frame,
            exportselection=0
        )
        widg.grid(row=0, column=0)

    elif selection == 7:

        # enable prog_button in case it was disabled
        prog_button.config(state="active")

        config_label.config(
            text="The robot will "
                 "discard items at "
                 "this point and "
                 "it will revert to "
                 "the start of the "
                 "cycle\n"
                 "Move robot to the "
                 "position that you "
                 "wish to discard at, "
                 "select how often "
                 "items should be "
                 "discarded and hit "
                 "Save command"

        )

        widg = tk.Radiobutton(
            master=prgm_config_frame,
            variable=prgm_qc_type,
            value=0,
            text="Discard every Nth\nitem"
        )
        widg.grid(row=0, column=0)

        widg = tk.Radiobutton(
            master=prgm_config_frame,
            variable=prgm_qc_type,
            value=1,
            text="Discard based on\npercentage"
        )
        widg.grid(row=1, column=0)

        widg = tk.Entry(
            master=prgm_config_frame,
            exportselection=0
        )
        widg.grid(row=2, column=0)


def get_filename_entry():
    filename=prgm_config_frame.winfo_children()[0].get()
    save_program(2,filename)


def save_program(operation,file):
    if operation == 0:
        prog_label.config(
            text="Saving file"
        )
        prog_list.grid_forget()
        config_label.config(
            text="Select file to overwrite "
                 "or create a new savefile"
        )
        destroy_widg_children(prgm_config_frame,0)
        prog_button.grid_forget()
        save_button.config(
            text="Save",
            state="disabled",
            command=lambda m=2,z="":save_program(m,z)
        )
        avail_programs = os.listdir(global_vars.folder_path+"saved_programs")
        for i in range(len(avail_programs)):
            widg = tk.Button(
                master= prgm_config_frame,
                text=avail_programs[i],
                command=lambda m=2,z=avail_programs[i]:save_program(m,z)
            )
            widg.grid(row=i, column=0)
        widg = tk.Button(
            master=prgm_config_frame,
            text="New savefile",
            command=lambda m=1,z="":save_program(m,z)
        )
        widg.grid(row=len(avail_programs), column=0)
        print(avail_programs)
    if operation == 1:
        config_label.config(
            text="Enter a filename and "
                 "click Save"
        )
        destroy_widg_children(prgm_config_frame, 0)
        widg = tk.Entry(
            master=prgm_config_frame,
            exportselection = 0
        )
        widg.grid(row=0, column=0)
        save_button.config(
            state="active",
            command=get_filename_entry
        )
        save_program.new_file = 1

    if operation == 2:
        #!!!!!!!!!!!
        #this does not check if the filename is valid
        #!!!!!!!!!!!
        if file == "":
            config_label.config(
                text="No filename specified "
                     "Enter a filename and "
                     "click Save"
            )
            return
        save_program(3,file)

    if operation == 3:
        #saving file
        save_path = global_vars.folder_path+"saved_programs/"+file
        if save_program.new_file == 1:
            if not os.path.exists(save_path):
                os.makedirs(save_path)
        #reset new_file flag
        save_program.new_file=0

        moves_file_path = save_path+"/robot_moves.txt"
        states_file_path = save_path + "/robot_states.txt"
        discard_coords_file_path = save_path + "/discard_coords.txt"
        tm = open(global_vars.folder_path+"temp_moves.txt", "r")
        move_contents = tm.readlines()
        rm = open(moves_file_path, "w")
        for i in range(len(move_contents)):
            rm.write(move_contents[i])
        tm.close()
        rm.close()
        ts = open(global_vars.folder_path+"temp_states.txt", "r")
        state_contents = ts.readlines()
        rs = open(states_file_path, "w")
        for i in range(len(state_contents)):
            rs.write(state_contents[i])
        ts.close()
        rs.close()
        ds = open(discard_coords_file_path, "w")
        ds.write(str(global_vars.x_discard_position)+"\n")
        ds.write(str(global_vars.y_discard_position)+"\n")
        ds.write(str(global_vars.z_discard_position)+"\n")
        ds.close()
        #remake the program_selection widgets to get the new program in
        create_program_selection_widgets(0)
        #reset the menu
        record_program(-1)


save_program.new_file = 0


def record_program(operation):
    if operation == -1:
        #reset
        for i in range(3):
            prgm_speed_vars[i].set(1)
            prgm_mm_delay_vars[i].set(0)
        prog_label.config(
            text="Click PROGRAM to start programming"
        )
        prog_button.config(
            text="PROGRAM",
            command=lambda i=0: record_program(i)
        )
        programming_frame.winfo_children()[6].grid_forget()
        programming_frame.winfo_children()[5].grid_forget()
        programming_frame.winfo_children()[3].grid_forget()
        programming_frame.winfo_children()[2].grid_forget()
        programming_frame.winfo_children()[1].grid_forget()

        prog_button.grid(row=4, column=0)
        prog_button.config(state="active")
        save_button.config(
            text="Save program",
            command=lambda i=3: record_program(i)
        )
        #re-pack program_select_frame
        program_select_frame.pack(pady=(10, 0), padx=20)
        # re-pack ignore_phys_switch_button
        ignore_phys_switch_button.pack(pady=(10, 0), padx=20)



    if operation == 0:
        if (global_vars.servo_errors >> 5) & 1 == 1:
            prog_label.config(text="Robot has to be zeroed\nbefore programming")
            return
        prog_label.config(text="Move robot to the desired\nstart position and click save")
        prog_button.config(text="Save initial position")
        prog_button.config(command=lambda i=1: record_program(i))
        save_button.config(state="disabled")
        # open temp_moves and temp_states in write mode to clear anything writen to it
        f = open(global_vars.folder_path+"temp_moves.txt", "w")
        f.write("v 0.1")
        f.close()
        f = open(global_vars.folder_path+"temp_states.txt", "w")
        f.write("v 0.1")
        f.close()
        # reset temp_moves_index value
        record_program.temp_moves_index = 0
        # hide program_select_frame
        program_select_frame.pack_forget()
        # hide ignore_phys_switch_button
        ignore_phys_switch_button.pack_forget()

    if operation == 1:
        prev_position[0] = global_vars.x_position
        prev_position[1] = global_vars.y_position
        prev_position[2] = global_vars.z_position
        start_position[0] = prev_position[0]
        start_position[1] = prev_position[1]
        start_position[2] = prev_position[2]
        print("Start position is :")
        print(start_position)
        prog_label.config(text="Select action")
        prog_button.config(text="Save command")
        prog_button.config(command=lambda i=2: record_program(i))
        prog_list.grid(row=1, column=0)
        edit_list.grid(row=1, column=1)
        save_button.grid(row=5, column=0, pady=(10, 0))
        reset_prog_button.grid(row=6, column=0, pady=(5, 0))


    if operation == 2:
        if len(prog_list.curselection()) == 0:
            print("nothing selected")
        else:
            save_button.config(state="active")
            if prog_list.curselection()[0] == 0:
                print("programmin imm in")
                prg_string = "i.in."
                prg_char_len = 7

            elif prog_list.curselection()[0] == 1:
                print("programmin imm out")
                prg_string = "i.out."
                prg_char_len = 8

            elif prog_list.curselection()[0] == 2:
                print("programmin zmod in")
                prg_string = "z.in."
                prg_char_len = 3

            elif prog_list.curselection()[0] == 3:
                print("programmin zmod out")
                prg_string = "z.out."
                prg_char_len = 3

            elif prog_list.curselection()[0] == 4:
                print("programmin move")
                # write data to robot_moves
                for i in range(len(prg_moving_axes)):
                    record_program.saved_moves += 1
                    if prg_moving_axes[i] == "X":
                        prg_string = "\n1." + str(global_vars.x_position) + "." + str(
                            prgm_speed_vars[0].get()) + "." + str(prgm_mm_delay_vars[0].get())
                    elif prg_moving_axes[i] == "Y":
                        prg_string = "\n2." + str(global_vars.y_position) + "." + str(
                            prgm_speed_vars[1].get()) + "." + str(prgm_mm_delay_vars[1].get())
                    else:
                        prg_string = "\n3." + str(global_vars.z_position) + "." + str(
                            prgm_speed_vars[2].get()) + "." + str(prgm_mm_delay_vars[2].get())
                    # increment temp_moves_index
                    record_program.temp_moves_index += 1
                    f = open(global_vars.folder_path+"temp_moves.txt", "a")
                    f.write(prg_string)
                    f.close()
                    # update prev_positions
                    prev_position[0] = global_vars.x_position
                    prev_position[1] = global_vars.y_position
                    prev_position[2] = global_vars.z_position

                first_move_index = record_program.temp_moves_index - len(prg_moving_axes)
                prg_string = "s.move." + str(first_move_index) + "\ns.compl." + str(record_program.temp_moves_index - 1)
                prg_char_len = 0

            elif prog_list.curselection()[0] == 5:
                invalid_ms = 0
                try:
                    ms_delay = int(prgm_config_frame.winfo_children()[0].get())
                    if ms_delay < 1:
                        invalid_ms = 1
                except:
                    invalid_ms = 1

                if invalid_ms == 1:
                    config_label.config(
                        text="Invalid selection\nInput a number >1"
                    )
                    return
                prg_string = "d." + str(ms_delay)
                prg_char_len = 0
            elif prog_list.curselection()[0] == 6:
                invalid_discard = 0
                try:
                    discard_num = int(prgm_config_frame.winfo_children()[0].get())
                    if discard_num < 1:
                        invalid_discard = 1
                except:
                    invalid_discard = 1

                if invalid_discard == 1:
                    config_label.config(
                        text="Invalid selection\nEnter a number >1"
                    )
                    return
                # update startup discard position
                global_vars.x_discard_position = global_vars.x_position
                global_vars.y_discard_position = global_vars.y_position
                global_vars.z_discard_position = global_vars.z_position
                print("Discarding (startup) at :" + str(global_vars.x_discard_position) + "." + str(global_vars.y_discard_position) + "." + str(global_vars.z_discard_position))
                prg_string = "r.disc." + str(discard_num)
                prg_char_len = 0

            elif prog_list.curselection()[0] == 7:
                invalid_discard = 0
                error_str = ""
                if prgm_qc_type.get() == 0:
                    discard_type = "s"
                    # static discard
                    try:
                        discard_num = int(prgm_config_frame.winfo_children()[2].get())
                        if discard_num < 1:
                            invalid_discard = 1
                            error_str = "Enter a number >1"
                    except:
                        invalid_discard = 1
                        error_str = "Enter a number >1"
                else:
                    # percent discard
                    discard_type = "p"
                    try:
                        discard_num = int(prgm_config_frame.winfo_children()[2].get())
                        if discard_num < 1 or discard_num > 100:
                            invalid_discard = 1
                            error_str = "Enter a number between\n1 and 100"
                    except:
                        invalid_discard = 1
                        error_str = "Enter a number between\n1 and 100"

                if invalid_discard == 1:
                    config_label.config(
                        text="Invalid selection\n" + error_str
                    )
                    return
                # update startup discard position
                global_vars.x_qc_discard_position = global_vars.x_position
                global_vars.y_qc_discard_position = global_vars.y_position
                global_vars.z_qc_discard_position = global_vars.z_position
                print("Discarding (QC) at :" + str(global_vars.x_qc_discard_position) + "." + str(global_vars.y_qc_discard_position) + "." + str(global_vars.z_qc_discard_position))
                prg_string = "r.qc." + discard_type + "." + str(discard_num)
                prg_char_len = 0

            if prg_char_len == 0:
                pass
            else:
                for i in range(prg_char_len):
                    prg_string += prg_char_value[i]

            print(prg_string)
            f = open(global_vars.folder_path+"temp_states.txt", "a")
            f.write("\n")
            f.write(prg_string)
            f.close()

            # reset the listmenu
            prog_list.event_generate("<<ListboxSelect>>")

    if operation == 3:
        if (prev_position[0] != start_position[0] or
                prev_position[1] != start_position[1] or
                prev_position[2] != start_position[2]):
            config_label.config(
                text="The robot has to return "
                     "at the starting position "
                     +str(start_position[0])+"."+str(start_position[1])+"."+str(start_position[2])+"\n"
                     "for a valid program"
            )
            return

        if record_program.saved_moves == 0:
            config_label.config(
                text="At least 2 moves must be "
                     "programmed for a valid "
                     "program"
            )
            return

        if record_program.saved_moves > 60:
            config_label.config(
                text="Robot supports up to 60 "
                     "moves, limit was exceeded"
            )
            return
        save_program(0,0)


record_program.temp_moves_index = 0
record_program.saved_moves = 0


def get_input():
    user_input = debug_entry.get()
    #parse data by funct.read_user_input
    funct.read_user_input(user_input)
    

imm_inputs = [
    "Mold Closed",
    "Automatic",
    "Ejector Forward",
    "Ejector Retracted",
    "Movable Gates Closed",
    "Mold Open",
    "Emergency Stop"
]
imm_outputs = [
    "Not Usable",
    "Mold Open",
    "Ejector Forward",
    "Ejector Retract",
    "Robot Non-Operational",
    "Emergency Stop",
    "Mold Area Free",
    "Mold Close"
]

servo_errors = [
    "Program Loaded",
    "Servo Restarted",
    "Axes Zeroed",
    "Move aborted - Getting pulses",
    "Unable to enter Auto mode",
    "Invalid Servo mode",
    "Requested move out of bounds",
    "Alarm"
]
servo_status = [
    "next_flag",
    "z_zeroing",
    "y_zeroing",
    "x_zeroing",
    "z_direction",
    "y_direction",
    "x_direction",
    "z_inductive",
    "y_inductive",
    "x_inductive",
    "z_move_end",
    "y_move_end",
    "x_move_end",
    "z_move_start",
    "y_move_start",
    "x_move_start"
]

zmod_inputs = [
    "Input 3",
    "Input 2",
    "Gripper input"
]
zmod_outputs = [
    "Relay 3",
    "Relay 2",
    "Gripper"
]

# ui variables
start_position = [0, 0, 0]
prev_position = [0, 0, 0]
prg_char_value = ['*'] * 8
prg_moving_axes = []



root = tk.Tk()
root.title("Robot UI")
toggle_fullscreen()
#root.grid_columnconfigure(1, weight=1)
main_container = tk.Frame(root)
screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()
canvas = tk.Canvas(
    master=main_container,
    width=screen_width-20,
    height=screen_height
)
y_scroll = tk.Scrollbar(main_container, width=20, orient="vertical", command=canvas.yview)
scrolling_frame = tk.Frame(
    master=canvas
)

scrolling_frame.bind(
    "<Configure>",
    lambda e: canvas.configure(scrollregion=canvas.bbox("all"))
)

canvas.create_window((0,0),window=scrolling_frame,anchor="nw")
canvas.configure(yscrollcommand=y_scroll.set)

main_container.pack()
canvas.pack(side="left",fill="both",expand=True)
y_scroll.pack(side="right",fill="y")

#true_image = tk.PhotoImage(file="\ui_images\true.png")
true_image = tk.PhotoImage(file=global_vars.folder_path+"ui_images/true.png")
false_image = tk.PhotoImage(file=global_vars.folder_path+"ui_images/false.png")
not_updated_image = tk.PhotoImage(file=global_vars.folder_path+"ui_images/not_updated.png")
arrow_negative = tk.PhotoImage(file=global_vars.folder_path+"ui_images/move_negative.png")
arrow_positive = tk.PhotoImage(file=global_vars.folder_path+"ui_images/move_positive.png")
arrow_up = tk.PhotoImage(file=global_vars.folder_path+"ui_images/move_up.png")
arrow_down = tk.PhotoImage(file=global_vars.folder_path+"ui_images/move_down.png")
stop_image = tk.PhotoImage(file=global_vars.folder_path+"ui_images/stop.png")
manual_image = tk.PhotoImage(file=global_vars.folder_path+"ui_images/manual.png")
manual_dis_image = tk.PhotoImage(file=global_vars.folder_path+"ui_images/manual_disabled.png")
auto_image = tk.PhotoImage(file=global_vars.folder_path+"ui_images/auto.png")
auto_dis_image = tk.PhotoImage(file=global_vars.folder_path+"ui_images/auto_disabled.png")

# window.rowconfigure(0,minsize=500)
# window.rowconfigure(1,minsize=200)
# window.columnconfigure(0,minsize=500)
# window.columnconfigure(1,minsize=200)



# main frames
variables_frame = tk.Frame(
    master=scrolling_frame#,
    #highlightthickness=2,
    #highlightbackground="purple"
)
menu_frame = tk.Frame(
    master=scrolling_frame#,
    #highlightthickness=2,
    #highlightbackground="red"
)


controls_frame = tk.Frame(
    master=scrolling_frame#,
    #highlightthickness=2,
    #highlightbackground="green"
)

variables_frame.grid(row=0, column=0, sticky="news", padx=(20,0))
menu_frame.grid(row=0, column=1, sticky="nes", padx=0)
controls_frame.grid(row=1, column=0, columnspan=2, sticky="news", padx=(20,0))
controls_frame.columnconfigure(0, weight=1)
controls_frame.columnconfigure(1, weight=1)


# varuables_frame subframes
frame_imm = tk.Frame(
    master=variables_frame,
    highlightbackground="grey",
    highlightthickness=2
)
frame_servo = tk.Frame(
    master=variables_frame,
    highlightbackground="grey",
    highlightthickness=2
)
frame_zmod = tk.Frame(
    master=variables_frame,
    highlightbackground="grey",
    highlightthickness=2
)
# subrames labels
imm_label = tk.Label(
    master=variables_frame,
    text="IMM Status",
    font=("TkDefaultFont", 14)
)
servo_label = tk.Label(
    master=variables_frame,
    text="Robot Status",
    font=("TkDefaultFont", 14)
)
zmod_label = tk.Label(
    master=variables_frame,
    text="Zmod Status",
    font=("TkDefaultFont", 14)
)
imm_label.pack(pady=(5, 0))
frame_imm.pack(side=tk.TOP, pady=(5, 5))
servo_label.pack()
frame_servo.pack(side=tk.TOP, pady=(5, 5))
zmod_label.pack()
frame_zmod.pack(side=tk.TOP, pady=(5, 5))

# frame_imm subframes
# create_widgets(vars, master, type, function , column_num, row, column )
create_widgets(imm_inputs, frame_imm, "INPUT", "NONE", 2, 0, 0)
create_widgets(imm_outputs, frame_imm, "OUTPUT", set_ui_outputs, 2, 0, 1)

# frame_servo subframes
create_widgets(servo_errors, frame_servo, "INPUT", "NONE", 3, 0, 0)
#create_widgets(servo_status, frame_servo, "INPUT", "NONE", 2, 0, 1)

position_info_frame = tk.Frame(
    master=frame_servo
)
position_info_frame.grid(row=1, column=0, columnspan=2)
x_pos_label = tk.Label(
    master=position_info_frame,
    text="X Position\n Unknown",
    font=("TkDefaultFont", 14)
)

y_pos_label = tk.Label(
    master=position_info_frame,
    text="Y Position\n Unknown",
    font=("TkDefaultFont", 14)
)

z_pos_label = tk.Label(
    master=position_info_frame,
    text="Z Position\n Unknown",
    font=("TkDefaultFont", 14)
)

x_pos_label.grid(row=0, column=0, padx=20, pady=5)
y_pos_label.grid(row=0, column=1, padx=20, pady=5)
z_pos_label.grid(row=0, column=2, padx=20, pady=5)

# frame_zmod subframes
create_widgets(zmod_inputs, frame_zmod, "INPUT", "NONE", 1, 0, 0)
create_widgets(zmod_outputs, frame_zmod, "OUTPUT", set_ui_outputs, 1, 0, 1)





# controls subframes

# manual control frame
manual_position_frame = tk.Frame(
    master=controls_frame,
    highlightbackground="grey",
    highlightthickness=2
)
manual_position_frame.grid(row=0, column=0)

manual_position_axes = [
    "X axis",
    "Y axis",
    "Z axis"
]

for i in range(3):
    # print("i is  :"+str(i))
    control_label = tk.Label(
        master=manual_position_frame,
        text=manual_position_axes[i],
        font=("TkDefaultFont", 14)
    )
    negative_button = tk.Button(
        master=manual_position_frame,
        image=arrow_negative
    )
    positive_button = tk.Button(
        master=manual_position_frame,
        image=arrow_positive
    )
    negative_button.bind("<ButtonPress-1>", lambda event, i=i: click_negative(event, i))
    positive_button.bind("<ButtonPress-1>", lambda event, i=i: click_positive(event, i))
    negative_button.bind("<ButtonRelease-1>", lambda event, i=i: released_manual_move(event, i))
    positive_button.bind("<ButtonRelease-1>", lambda event, i=i: released_manual_move(event, i))

    # vertical grid
    # control_label.grid(row=0+(i*2), column=0, columnspan= 2)
    # negative_button.grid(row=1+(i*2), column=0, sticky=tk.E)
    # positive_button.grid(row=1+(i*2), column=1, sticky=tk.W)

    # horizontal grid
    control_label.grid(row=0, column=2 * i, columnspan=2)
    negative_button.grid(row=1, column=2 * i)
    positive_button.grid(row=1, column=(2 * i) + 1)

speed_manual_frame = tk.Frame(
    master=manual_position_frame
)
speed_manual_frame.grid(row=0, column=6, rowspan=2)

speed_label = tk.Label(
    master=speed_manual_frame,
    text="Manual movement speed",
    font=("TkDefaultFont", 14)
)
speed_label.grid(row=0, column=0, columnspan=2)

manual_speed = tk.IntVar()
speed_selections = [
    1,
    5,
    20,
    50,
    100
]
manual_speed.set(speed_selections[0])
for i in range(len(speed_selections)):
    radio_but = tk.Radiobutton(
        master=speed_manual_frame,
        text=str(speed_selections[i]) + "%",
        variable=manual_speed,
        value=speed_selections[i]
    )
    radio_but.grid(row=1 + int(i / 2), column=(i % 2), sticky=tk.N)

# move by coordinates frame
coord_move_frame = tk.Frame(
    master=manual_position_frame
)
coord_move_frame.grid(row=2, column=0, columnspan=8)

coord_text = ["", "", ""]
coord_labels = [
    "X",
    "Y",
    "Z"
]
for i in range(3):
    coord_label = tk.Label(
        master=coord_move_frame,
        text=coord_labels[i],
        font=("TkDefaultFont", 14)
    )
    coord_label.grid(row=0, column=i)
    coord_text[i] = tk.StringVar()
    coord_text[i].set("NaN")
    coord_entry = tk.Entry(
        master=coord_move_frame,
        textvariable=coord_text[i],
        width=10
    )
    coord_entry.grid(row=1, column=i, padx=5)

coord_move_button = tk.Button(
    master=coord_move_frame,
    text="Move to position",
    command=lambda i=0: servo_move(i)
)

coord_move_s_button = tk.Button(
    master=coord_move_frame,
    text="Safe Move to position",
    command=lambda i=1: servo_move(i)
)
coord_move_button.grid(row=2, column=1, pady=5)
coord_move_s_button.grid(row=3, column=1, pady=5)


#auto mode frame
auto_mode_frame = tk.Frame(
    master= controls_frame,
    highlightcolor="grey",
    highlightthickness=2
)


cycles_completed_label = tk.Label(
    master=auto_mode_frame,
    text="Cycles completed\n"
         +str(global_vars.cycles),
    font=("TkDefaultFont", 14)
)
cycles_completed_label.grid(row=0, column=0, sticky="n")

items_completed_label = tk.Label(
    master=auto_mode_frame,
    text="Items completed\n"
         +str(global_vars.items_completed),
    font=("TkDefaultFont", 14)
)
items_completed_label.grid(row=1, column=0, sticky="n")

items_discarded_su_label = tk.Label(
    master=auto_mode_frame,
    text="Items discarded (Startup)\n"
         +str(global_vars.items_discarded),
    font=("TkDefaultFont", 14)
)
items_discarded_su_label.grid(row=2, column=0, sticky="n")

items_discarded_qc_label = tk.Label(
    master=auto_mode_frame,
    text="Items for Quality Control\n"
         +str(global_vars.items_for_qc),
    font=("TkDefaultFont", 14)
)
items_discarded_qc_label.grid(row=3, column=0, sticky="n")


# other controls frame
other_controls_frame = tk.Frame(
    master=controls_frame,
    highlightbackground="grey",
    highlightthickness=2
)
other_controls_frame.grid(row=0, column=1, padx=20, sticky="e")

stop_button = tk.Button(
    master=other_controls_frame,
    image=stop_image,
    border=0,
    command=lambda m=0,z=0:released_manual_move(m, z)
)

manual_button = tk.Button(
    master=other_controls_frame,
    image=manual_dis_image,
    border=0,
    command=lambda m=0, z=1: change_mode(m, z)
)

auto_button = tk.Button(
    master=other_controls_frame,
    image=auto_dis_image,
    border=0,
    command=lambda m=1, z=1: change_mode(m, z)
)

if global_vars.ignore_physical_switch == 0:
    manual_button.config(state="disabled")
    auto_button.config(state="disabled")

stop_button.grid(row=0, column=0)
manual_button.grid(row=1, column=0)
auto_button.grid(row=2, column=0)

user_input_frame = tk.Frame(
    master=other_controls_frame
)
user_input_frame.grid(row=3, column=0, pady=(5, 0))

debug_entry_label = tk.Label(
    master=user_input_frame,
    text="User input"
)
#debug_entry_label.grid(row=0, column=0)

debug_entry = tk.Entry(
    master=user_input_frame,
    exportselection=0
)
debug_entry.grid(row=1, column=0)

widg = tk.Button(
    master=user_input_frame,
    text="Update",
    command=get_input
)
widg.grid(row=2, column=0)



# programming frame
programming_frame = tk.Frame(
    master=menu_frame,
    highlightbackground="grey",
    highlightthickness=2
)
#programming_frame.grid(row=0, column=0, pady=(10, 0), padx=20, sticky="ns")
programming_frame.pack(pady=(10, 0), padx=20)

prog_label = tk.Label(
    master=programming_frame,
    text="Click PROGRAM to\nstart programming",
    font=("TkDefaultFont", 11)
)

prog_list = tk.Listbox(
    master=programming_frame
)
prog_list.insert(1, "Wait for IMM signals")
prog_list.insert(2, "Set IMM relays")
prog_list.insert(3, "Wait for ZMOD signals")
prog_list.insert(4, "Set ZOMD relays")
prog_list.insert(5, "Move")
prog_list.insert(6, "Wait (milliseconds)")
prog_list.insert(7, "Discard (startup)")
prog_list.insert(8, "Discard (QC)")
prog_list.bind("<<ListboxSelect>>", list_change)


edit_list = tk.Listbox(
    master=programming_frame
)


config_label = tk.Label(
    master=programming_frame,
    text="",
    wraplength=150
)

prgm_config_frame = tk.Frame(
    master=programming_frame#,
    #highlightbackground="blue",
    #highlightthickness=2
)

prog_button = tk.Button(
    master=programming_frame,
    text="PROGRAM",
    command=lambda i=0: record_program(i)
)

save_button = tk.Button(
    master=programming_frame,
    text="Save program",
    command=lambda i=3: record_program(i)
)

reset_prog_button = tk.Button(
    master=programming_frame,
    text="Reset Program",
    command=lambda i=-1: record_program(i)
)

file_name_entry = tk.Entry(
    master=programming_frame,
    exportselection=0
)

prog_label.grid(row=0, column=0)
prog_button.grid(row=4, column=0, pady=(5, 0))





prgm_speed_vars = [0, 0, 0]
prgm_mm_delay_vars = [0, 0, 0]
prgm_qc_type = tk.IntVar()

for i in range(3):
    prgm_speed_vars[i] = tk.IntVar()
    prgm_mm_delay_vars[i] = tk.IntVar()

# Program select frame
program_select_frame = tk.Frame(
    master=menu_frame,
    highlightbackground="grey",
    highlightthickness=2
)
program_select_frame.pack(pady=(10, 0), padx=20)
program_select_label = tk.Label(
    master=program_select_frame,
    text="Program Selection Menu",
    font=("TkDefaultFont", 11)
)
program_select_label.grid(row=0, column=0)
create_program_selection_widgets(0)

#ignore_physical_button button
ignore_phys_switch_button = tk.Button(
    master=menu_frame,
    text="Ignore Physical\nSwitch",
    command=change_ignore_phys_switch
)
ignore_phys_switch_button.pack(pady=(10, 0), padx=20)



update_whole_ui()
