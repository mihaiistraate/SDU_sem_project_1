# Multimeter

The development of high-tech devices plays an essential role in the modern world. One of these devices is a multimeter, which has been the focus of this semester project. Throughout this journey, not only technical skills have been used, but also teamwork and collaboration have been developed, as the multifunctional digital multimeter was designed, built, and evaluated.

The primary objective was to develop a digital multimeter, which is an electronic device that can measure several parameters of certain electronic components or electrical properties. Typical multimeters can measure current, voltage and more. In order to fulfil the requirements of the assignment, it was mandatory to measure four electronic properties, of which two were mandatory: resistance and voltage. The last two were voluntarily chosen by the team. Current and temperature have been chosen to enhance the versatility of the device, making it a more comprehensive tool for various diagnostic and experimental scenarios.

The product development process had four main stages, which are research, designing, building and testing. The Gantt chart was used to showcase the project timeline and to make sure the team is in time to finalize the project within the given timeframe. It can be seen in the following picture:

<img width="1779" height="320" alt="gantt chart" src="https://github.com/user-attachments/assets/3a4e7c05-9f18-44de-bb8b-85b5cacad938" />

There was a fixed budget from the university of 1k DKK to order components necessary for the PCB and enclosure. As it can be seen in the following picture, only 245 DKK have been used.

<img width="1839" height="735" alt="components list" src="https://github.com/user-attachments/assets/cfd96bf6-a1bf-4efb-86ad-cf7bcbfe0c9d" />

In the research phase, information was collected from different lectures; additionally further research was done for this purpose. Hereafter, the project started to take shape, and the designing and gathering all the material stages came. These phases gave a better insight in how a multimeter works, and how planning should be done to meet the given requirements.

During the designing phase, a schematic was created, which was later used for building a whole circuit. KiCad 7.0 was used; a schematic and a PCB layout have been generated. The manufacturing of the PCB was done by the PCB miling team on campus:

<img width="2000" height="660" alt="arduino nano pinout" src="https://github.com/user-attachments/assets/5e43bc63-f343-4daa-abf3-0e10a0f1cf38" />
<img width="1963" height="1355" alt="PCB schematic" src="https://github.com/user-attachments/assets/874af4bc-9853-4dab-92df-781106ca2832" />
<img width="1511" height="1050" alt="PCB layout" src="https://github.com/user-attachments/assets/c751a1fb-6e67-48e0-b5e4-28697c91a668" />

Moreover, the case had to be 3D printed, which allowed members to tailor the design to the specific needs of the project and to explore the possibilities of contemporary fabrication methods. It was planned to use the 3D printers available for students in the student workshop, however, that came with unforeseen issues. The 3D printers were heavily used and a lot of quality issues have been encountered when trialling the prints. However, after multiple unsuccessful prints, the team was able to revise and modify the design, now knowing what had to be changed. In addition, the code writing process started. This process allowed for an understanding of the balance between aesthetic appeal, ergonomic efficiency, and structural integrity.

The building phase was divided into three stages. Firstly, soldering of the PCB was started. Secondly, the code was completed. Lastly, the elements were integrated and the components assembled into the 3D printed case. This phase was undoubtedly the most troublesome in response to unexpected issues, and the students gained a lot of profound knowledge in problem-solving.

To understand the usage of the product, a step-by-step description has been developed. In addition, a video was made: https://www.youtube.com/watch?v=Sm5R2FJd35g
1. To turn ON the device, the keylock switch has to be used.
2. During the startup process, the display will show a welcome message and a battery check.
3. The main menu will be shown, which can be navigated by pressing the four buttons.
4. The first button can be used to measure the temperature. The temperature sensor has to be connected to the right port on the multimeter. To quit this mode, the first button has to be pressed.
5. The second button can be used to measure resistance. Note the recommended range for this measurement. For this, the negative probe has to be connected to the ground and the positive one to the port labeled ‘R’. To quit this mode, the first button must be pressed.
6. The third button can be used to measure current. Note the recommended range for this measurement. For this, the negative probe has to be connected to the ground and the positive one to the port labeled ‘I’. To quit this mode, the first button has to be pressed.
7. The fourth button can be used to measure voltage. Note the recommended range for this measurement. For this, the negative probe has to be connected to the ground and the positive one to the port labeled ‘V’. To quit this mode, the first button has to be used.
8. For checking the voltage of the battery, the second and third buttons must be pressed and hold. To quit this mode, the first button must be presed.
9. To access the stopwatch, the first and fourth buttons need to be pressed and hold. After this, the instructions on how to operate the stopwatch will be shown on the display. To quit this mode, the first button must be pressed.

Nearing conclusion, only calibratation and conducting testing were needed. During the calibration process, various scenarios have been simulated to ensure that criteria of accuracy and reliability for standard multimeter was fulfilled by the product, in total being 20 for each parameter. For reference, a professional device has been used. The results can be seen in the following pictures:

<img width="1258" height="487" alt="voltage accuracy" src="https://github.com/user-attachments/assets/a785c6e8-ba65-4cbc-8423-8f6bac079fb7" />
<img width="719" height="521" alt="current accuracy" src="https://github.com/user-attachments/assets/6131112e-8b2c-46e4-9bc9-343ad33dfa89" />
<img width="1266" height="582" alt="resistance accuracy" src="https://github.com/user-attachments/assets/67c44a81-286a-4829-bd6f-467b047a2818" />
