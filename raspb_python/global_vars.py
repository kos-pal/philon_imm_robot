#v 0.1

#var list for use with wait_for_update and set_and_confirm functions
#1 imm_signals , binary string
#2 imm_relays , binary string
#3 servo_errors , binary string
#4 servo_status , binary string
#5 x_position , int
#6 y_position , int
#7 z_position , int
#8 servo_params , not implemented
#9 servo_mode , int
#10 servo_command_index , int
#11 auto_move_started , binary string
#12 auto_move_ended , binary string
#13 z_mod_inputs , binary string
#14 z_mod_outputs , binary string



global folder_path
#folder_path = "robot_ui_3/"
folder_path = ""

global disable_ui_updates
disable_ui_updates = 0


global ignore_physical_switch
ignore_physical_switch = 0

global raspb_state
raspb_state = "CONFIG"

global selected_program
selected_program = ""

global states_index
states_index = 0

global button_noise_r
button_noise_r = 0
global button_noise_f
button_noise_f = 0

global master_receiving
master_receiving = False
global master_transmiting
master_transmiting = False

global master_transm_ts
master_transm_ts = 0
global coms_out
coms_out = []
global coms_slave_requests
coms_slave_requests = []
global coms_release
coms_release =[]
global coms_timestamps
coms_timestamps = [0]*6



global auto_switch
auto_switch = 1

global led_status
led_status = 0

global robot_moves
robot_moves=[]

global x_start_position
x_start_position = 0
global y_start_position
y_start_position = 0
global z_start_position
z_start_position = 0

global x_discard_position
x_discard_position = 900
global y_discard_position
y_discard_position = 50
global z_discard_position
z_discard_position = 150

global x_qc_discard_position
x_qc_discard_position = 600
global y_qc_discard_position
y_qc_discard_position = 50
global z_qc_discard_position
z_qc_discard_position = 150

global robot_states
robot_states=[]

global items_completed
items_completed = 0
global items_discarded
items_discarded = 0
global items_for_qc
items_for_qc = 0
global num_discard
num_discard = 0
global cycles
cycles = 0

global imm_relays
imm_relays = -1

global imm_signals
imm_signals = -1
global imm_restart
imm_restart = -1



global servo_errors
servo_errors = -1
global servo_status
servo_status = -1
global x_status
x_status = "unknown"
global y_status
y_status = "unknown"
global z_status
z_status = "unknown"
global x_position
x_position = -1
global y_position
y_position = -1
global z_position
z_position = -1
global servo_params
servo_params = [-1]*21
global servo_mode
servo_mode = -1
global servo_command_index
servo_command_index = -1

global auto_move_started
auto_move_started = 0

global auto_move_ended
auto_move_ended = 0b111





global z_mod_inputs
z_mod_inputs = -1
global z_mod_outputs
z_mod_outputs = -1
global z_mod_restart
z_mod_restart = -1

    
    
