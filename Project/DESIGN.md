===========================================================================================

# FUTURADESK: DESIGN FILE
# AUTHOR: NATALY MORENO-MARTINEZ

===========================================================================================

## Technical Implementation of the Project: Summary

The website is built with Flask, Python, CSS, HTML, and Javascript. In addition to these software packages/languages, the website imports an audio file in the "Desktop" or "index.html" webpage.

## Python Structure

The python application.py serves as the backend script with connects all portions of the website API to Flask. It is strongly based off the work I submitted for the "finance" problem set, taking some functions and structures from my code for that website to implement features in futuradesk. The most similar feature of finance and Futuradesk are the login and new user pages, represented by the app routes "/login" and "/new_user."

Each route in the application.py script renders a template which responds to the user login status as well as form submissions. If a user submits invalid data, the python script returns "apology.html" with a catered message to the error. In addition to this webpage error response, the script contains an errorhandler for HTTPExceptions. The logout route cancels a user session, while the buffer, opener, and author routes simply redirect or render wedpage html templates.

## HTML Templates and structure

The layout.html file is the main backbone of the website, and contains meta tags to provide authorship and property descriptions. All HTML Templates except the "index.html" page extend the layout.html file with markdown code. The layout file contains four sections 
customizable markdown blocks:

1. The style block, to input CSS code specific to each webpage.
2. The script block, to input Javascript code specific to each webpage.
3. The background block, to alter the image(s) displayed by the body html tag in each webpage.
4. The main block, to insert the majority of the customized html structure for each webpage.

A markdown if clause determines if styles.css will be implemented in a webpage (only activated after users have logged in). The layout.html page also links bootstrap libraries and nicludes jQuery, Popper.js, and other bootstrap plugins for proper website structure and functionality. Additionally, the layout page contains the website icon. 

### Specific html file descriptions are listed below:

1. The apology.html webpage displays a centered image with text that can be customized in the python script. This serves as the error webpage.

2.  The author.html file includes a block of javascript which enables a "typewritter" effect. When the variable "text" is displayed in the "initializing" p tag in the html, the text appears to be typed on the spot. This was a stylistic desicion meant to make the website appear more interactive. 

3. The buffer.html includes a typewriter js function (much like the author.html typewriter feature) as well as a redirect feature which uses setTimeout to redirect to the homepage after a 3.5 second delay. This was also an artistic choice, to make the website seem more immersive.

4. The login.html page features a js function which flashes the "new user" link text, to point out the webpage. It uses setInterval to alter the text visibility of the element. To allow for the moving-letters effect on the "Accessing Terminal" homepage text, another javascript code snippet is embedded in the body html right after the text. The library is sourced in the file. Login contains a form which takes a username and password.

5. Much like the login page, the new_user.html file contains three form fields to allow a user to register themselves. These strings get inserted into a SQL database via a SQL execution call in the python application.py script.

6. The password change file contains a three field form which allows a user to change their password given a correct old username and password. The password is hashed and saved in the futuradesk.db SQL file via an execution call in the application.py app route '/passwordchange.'

7. The index file contains many features, including a fullscreen background that can be changed and music. The audio player is included in an audio tag at the beginning of the body html, under the taskbar "nav" tag. The audio tag is wrapped in a "draggable" division, to make it so that the element is draggable across the screen. This functionality is extended to the background change window, which has a "draggable2" id to also be able to be dragged. The separate ids are necessary to make it so that the second window can be hidden in their respective css codes.

## CSS

Much of the aesthetics and functionality of this website are dependent on the CSS files therein. The CSS is distributed into three parts:

1. The main styles.css file, which structure layout.html and most of the website page attributes (centering, text color, etc).
2. The nastyles.css file, which structures the index.html navigation bar and ensures correct position of dropdown menu elements.
3. The embedded style blocks in each webpage, while customize their elements.

Separating CSS code into these three groups was an organizational decision, given the navigation bar did not depend on the layout html formatting and each webpage had unique elements with complementary javascript code. The most important CSS (in my opinion) is represented by the #draggable and #draggable2 style rules in the index html page. These contain positions which are absolute, meaning their coordinates can be altered in javascript code (and therefore dragging these windows can be enabled). 

Much of the colorscheme, textual, and icon display was a stylistic choice, to enable the website to appear futuristic. An example of a stylistic effect is that of the fade in and out CSS rules in the "body" tag of the styles.css file. This includes a fade animation funciton, which changes the webpage body opacity as it loads and allows for a soft transition between webpages.

## Javascript

The javascript code conducts most of the webpage redirecting (that is not dependent on the python application.py file) as well as the html element features which do not require webpage reloading. Some examples include textual effects in the login and new user files, as well as the draggable screen effect in index.html. I mainly used setInterval and setTimeout to artificially extend the duration of an effect (as with making text flash in the login page or making the buffer page last 3.5 seconds before redirection).  
