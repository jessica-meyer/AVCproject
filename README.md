# ENGR 101 Project 3

## Autonomous Vehicle Challenge

This is the "README" file for the Autonomous Vehicle Challenge (AVC).

## Project Plan

### Team
|Name|Email|Role|
|----|-----|----|
|Oshane|pereramihi@myvuw.ac.nz|Programmer and Logic Guru|
|Jessica|meyerjess@myvuw.ac.nz|Programmer and Coordinator|
|Helene|finlayhele@myvuw.ac.nz|Architect (Pseudo Code)|
|Cam|jonescame2@myvuw.ac.nz|Hardware Guru|
|Cohen|fouriecohe@myvuw.ac.nz|Hardware|

### Roadmap
#### Planning
|START DATE|STATUS|TASK DESCRIPTION|RESPONSIBILITY|DEADLINE|OUTCOME|
|----------|------|----------------|--------------|--------|-------|
|1/5/25    |Completed |Project Plan    |All |12/5/25 ||
|13/5/25   |Completed |Progress Report |All		   |23/5/25 ||
|1/5/25    |Completed |Software design |Helene and Oshane|8/5/25 |Each phase has a detailed explantion of what the bot needs to do|
|1/5/25    |Completed |Pseudo code |Helene|12/5/25 |Pre-code pseudo code written|
|1/5/25    |Completed    |Base code plan and functions |Oshane |8/5/25||

#### Software
|START DATE|STATUS|TASK DESCRIPTION|RESPONSIBILITY|DEADLINE|OUTCOME|
|----------|------|----------------|--------------|--------|-------|
|1/5/25    |Completed |Phase 0 - Initialization |Oshane |8/5/25 |Robot resets all variables and gets ready to make its way through the track|
|1/5/25    |Completed |Phase 1 - Open door |Oshane |8/5/25 |Robot can make its way through quad 1|
|1/5/25    |Completed |Phase 2 - Follow line|Oshane |8/5/25 |Robot can make its way through quad 2|
|1/5/25    |Completed |Phase 3 - Maze |Jessica |15/5/25 |Robot can make its way through quad 3|
|15/5/25   |Completed |Phase 4 - Pillars and ball |Oshane |22/5/25|Robot is able to approach each pillar and then hit the ball off the table|
|15/5/25   |Completed |Phase 5 - Victory |Oshane and Jessica|22/5/25|Completed but not used|
|1/5/25    |Completed |Motor functions - forwards, back, stop, left, right|Oshane |8/5/25|Robot has the ability to complete a series of movements|
|1/5/25    |Completed |Door function |Oshane |8/5/25|Robot can connect to server and open the door|
|1/5/25    |Completed |Variable function - reset variables |Oshane |8/5/25|Function that can be called to reset any variables needed in the next phase|
|8/5/25    |Completed |Camera - Look up and down |Jessica |15/5/25|Camera can look up and down when needed|

#### Hardware
|START DATE|STATUS|TASK DESCRIPTION|RESPONSIBILITY|DEADLINE|OUTCOME|
|----------|------|----------------|--------------|--------|-------|
|1/5/25    |Completed |Moving Bot |Cam |6/5/25|Bot moves and chasis is rigid and reliable|
|1/5/25    |Completed |Motor optimizing - Wheels |Cam |15/5/25|Implemented PID|
|1/5/25    |Completed |Motor optimizing - Camera |Cam |25/5/25|The camera initializes at the start and sets to a consistent positions across runs|
|1/5/25    |Completed |Bot body - 3d printed |Cohen |15/5/25||
|7/5/25    |Complete |Camera motor mount |Cohen |8/5/25|Mounts great - stable|

#### Testing
|START DATE|STATUS|TASK DESCRIPTION|RESPONSIBILITY|DEADLINE|OUTCOME|
|----------|------|----------------|--------------|--------|-------|
|6/5/25    |Complete |Line detection test 1|All|8/5/25|First test for the lines work but the motors were set to the incorret motor numbers|
|6/5/25    |Complete |Gate open test 1|All|8/5/25|We were able to comunicate with the door but unable to send the password back to the gate so the gate did not open|
|6/5/25    |Complete|Forward test 1|All|6/5/25|Robot went backwards|
|6/5/25    |Complete|Line dection test 2|All|6/5/25|Robot was able to see line - once the robot lost line the robot stopped|
|7/5/25    |Complete |Camera test 1 |Jessica and Cohen |7/5/25 |The motor on the robot was faulty - we tested and switched the motor out.|
|7/5/25   |Complete |Phase 2 test 1 |Oshane and Helene|15/5/25|Robot followed the line-stoped when it saw red.camra was manualy adjusted downward to prevent the possiblity of seeing two lines|
|8/5/25   |Complete |Phase 2 test 2 |All|15/5/25|Robot would lose line on some turns and shoot off|
|8/5/25   |Complete |Phase 1 test 3 |All|15/5/25|An update to the git has broken phase 1 - robot moves to fast and loses line - door now shuts on robot|
|15/5/25   |Complete |Genral test |All|15/5/25|The Line dection for robot has broken - the robot goes backwards|
|16/5/25   |Complete |Updated line dection |Helene and Oshane|15/5/25|The Line dection for robot works|
|15/5/25   |Complete |Phase 3 test 1 |Helene and Oshane|15/5/25|Due to new line dectection the maze sends the robot into a spinning motion|
|22/5/25   |Complete |Phase 4 test 1 |Oshane and Cam|22/5/25|Camera ran into an issue of not being able to detect the blue pillar|
|22/5/25   |Not started |Phase 5 test 1||22/5/25||

### Software Design

Dividing each part of the track into separate phases. Each phase will have preset movements it can call on (eg. the code calls turnRight() when it needs to make a turn to the right).<br>
Our program will have six phases used to navigate the course zero being the first

#### Phase Zero: Initialization
Phase Zero is defined to set up and prevent any errors coming over from previous testing sessions.Phase zero creates a strait the robot will replace every time the software starts. 
The camera will start up and be set to the down position. This phase will take a few photos to make sure the colours are correct on the camera. 
The robot will center itself on the line to prepare for Phase One

#### Phase One: Door Passage and Movement
Immediately after Phase 0 is completed, Phase 1 begins. The robot initiates this phase by opening the door. Once the door is fully open, the robot starts moving forward. 
While in motion, it continuously maintains its alignment by using the same visual feedback method from Phase 0: it monitors the distance from the detected line to the left and 
right edges of the camera's field of view. The robot dynamically adjusts its path to keep these distances approximately equal, within a specified error margin, ensuring it remains straight. 
The robot continues this motion until the door closes behind it, at which point it immediately stops.

#### Phase Two: Forward Navigation and Stop Condition
Upon completing Phase 1, the robot enters Phase 2, where it continues moving forward. Throughout this phase, the robot maintains its alignment using the same method as before — continuously measuring the distance between the detected line and the left and right edges of the camera’s field of view. It makes real-time adjustments to ensure these distances remain approximately equal within a set margin of error. The robot proceeds in this manner until it detects a red color at the top of its camera view, which serves as a visual stop signal. Once red is detected, the robot halts its movement.

#### Phase Three: The Maze
In Phase 3, the robot enters a maze and continues moving forward while maintaining its alignment using the same method as in the previous phases—measuring the distance from the 
line to the left and right edges of the camera’s field of view and adjusting its position to keep these distances approximately equal within a specified error margin. 
As the robot navigates, it reacts to specific visual cues: each time it detects the top part of the line, it performs a turn in a set sequence—first a 90° right turn, followed by a 
90° left turn on the next detection, another 90° left turn on the third detection, and finally a 90° right turn on the fourth detection. As it proceeds further, if the robot stops 
detecting the line on both the left and right sides, it interprets this as an instruction to turn—first a 90° left turn, and on the next such instance, a 90° right turn. The robot 
continues navigating the maze using these visual cues and alignment adjustments until it detects red at the top of the camera view, which signals the end of this phase and brings 
it to a stop.

#### Phase Four: Pillars and the ball
In Phase four the Robot no longer follows the black line and the robot's camera will be tilted up. The robot's goal now is to locate the three coloured pillars (colour,colour,colour) then move forward and get as close as possible to the coloured cylinders without hitting them. When the robot gets within the specified distance to each pillar the bot will halt any movement. The robot will now back itself up, turn to its left and then search for the next pillar by looking for a specific colour. The  Robot will go towards the pillar's order based upon colours. When the robot has finished navigating to each pillar, It proceeds by detecting the red ball. The robot will take its time to push the red ball off the table, without going over the edge itself

#### Phase Five: Victory Ritual
The robot will perform a combination of 360-degree spins and vertical camera movements as its victory dance.

### Hardware Info

3 - Camera<br>
1 - left motor<br>
5 - right motor<br>
48 - stop<br>
31 - direction 1<br>
61 - direction 2<br>

---
