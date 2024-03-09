A graphical interface implemented in C++ using the Qt library. This is the client program in the NBuilding application that communicates with the server program via the UDP
protocol. The NBuilding application provides and manages information about the classrooms/buildings of Alexandru Ioan Cuza University in Iasi. In this application, two types of 
users can connect: administrators and visitors. A visitor user will only be able to view information about the classrooms/buildings of the University. For a user to log in as an
administrator, they will need to enter a username and password, which will be transmitted to the server and searched in the database. If this admin exists in the database, 
they will have new options compared to a visitor, such as adding/deleting/modifying classroom/building information. Additionally, the program can download pictures from the server
so that the user can visualize the interior of a classroom.This application also features a filtering option, allowing users to find rooms based on desired criteria.
