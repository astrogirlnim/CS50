===============================================================================================================================			       
#FUTURADESK README
#AUTHOR: NATALY MORENO-MARTINEZ

===============================================================================================================================
# Futuradesk: 

Futuradesk is a Flask-application website desktop simulator, written in Python, CS, HTML and Javascript.

## Installation/Compilation and Running the Application

Please follow these instructions to install and compile the Futuradesk library in linux programming environments:

1. Download the "futura.zip" project folder.
2. Unzip the file by opening the terminal in the futura.zip folder directory and run "unzip futura.zip."
3. Run "cd futura" to enter the futura main folder.
4. Type "flask run" in the command line (in the futura directory).
5. Click the flask url to visit the futura webpage.

## Usage and Features

The Futuradesk web API simulates a futuristic desktop/OS. Upon opening the website, users will be redirected to the login screen. A text animation saying "Accessing Terminal" will greet the user. Below the animated text are two form input spaces, one which says "Identification" and another "Keypass." The Identification form takes a username, while the Keypass form input takes a corresponding password. When the user inputs a valid username-password combination and presses the enter key or clicks the "Probe" button, he will be redirected to a buffering and then desktop screen. If an invalid username-password combination is submitted, the user is redirected to an error page.

First time users can create a username and password by clicking the "New User?" text flashing on the top of the login webpage. This link will redirect users to the register homepage, which contains three form fields and a "Register Entity" submission button. The first form field "Identification" corresponds to the new username. The Keypass and Confirmation fields take a password. Both Keypass and Confirmation fields must match before a user can be added to the website database. If an invalid combination is submitted, the user is redirected to an error page. Once a valid username-password combination is inputted, the user is redirected to the login page (where they can input their new credentials). 

After logging in, the buffering page should load for 2-4 seconds before redirecting users to the simulated desktop. The desktop has many features, including:

1. A fullscreen gif background.
2. A taskbar at the top of the screen, with a dropdown menu below the "Initialize" button.
3. A draggable background music player. Upon clicking play, the music will loop until the user pauses the player again.
4. A draggable background screen personalizer/selector. The user can find this feature by going to the dropdown meny and clicking "Change background." A new draggable window will pop up with background images. If any of these images are selected, the background will change to the corresponding image. This window can be closed by clicking the "close" button.
5. An author's note page. The page can be found by going to the dropdown menu and clicking on "The Creator's Message." Users will be redirected to a page with text which appears gradually, until a message is revealed in the center of the screen. 
6. The exit button, which allows users to log out and redirects them to the login screen.

In addition to these features, the website features soft webpage transitions which fade in and out between webpages. The pointer is also replaced by a fractal icon which expands when hovering over a link or interactable feature of the website.

## Thank you!

Thank you to Christie and to CS50 course heads for a great year!

