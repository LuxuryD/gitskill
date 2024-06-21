### 1 Overview

In this assignment we concentrate on features that will make this application more user-friendly. We will add support to create convenient strategies to invest in a portfolio. We will also add a graphical user interface to our program.

### 2 Graphical User Interface

Add a new view to your application, that uses a graphical user interface. You are required to use Java Swing to create your GUI. You must design this so that your application can work with either the text-based view that you currently have, or the new graphical user interface (both views must co-exist).

Start by thinking about the similarities and differences between your views, and observing which operations you need. Although different views look and behave differently, there are some common aspects to all views. A common design technique is to have a view interface that has all functionalities and then individual views suppress or provide defaults for functionalities they do not implement. Another relevant design rule is from the SOLID principles: Interface Segregation (No client should be forced to depend on methods that it does not use). Think about these aspects as you come up with a design for your views.

Interaction, or "back-and-forth between the user and the program" makes the role of a controller more well-defined and non-trivial than it may have seemed in the previous assignments. Like views and models, controllers are best described as an interface whose purpose is to mediate the interactions between the view and the model. Multiple implementations of controllers are possible — potentially a specialized one for every model/view pairing. However it is also possible to implement a single controller that works for all your views: it depends on your design.

Your graphical user interface should offer only the following functionality:

- The ability to create a new portfolio
- The ability to buy/sell stocks by specifying the stock, number of shares, and date
- The ability to query the value and composition of a portfolio at a certain date
- The ability to save and retrieve portfolios from files

You are free to design the interaction in any way you wish. However your application must meet the following standards:

- Your GUI should not look and feel like a graphical equivalent of your text-based interface. For example, a sequence of pop-ups that correspond to the sequence of inputs in your text-based interface is not acceptable.
- The application must provide visual cues about what input is expected (e.g. a hard-to-guess sequence of keystrokes to do something is not acceptable).
- The application must provide visual cues about the effect that a user’s input has had. The user shouldn't have to wait to give more inputs to know that the program accepted the previous inputs.
- The appearance of your user interface should be reasonable. Oddly sized buttons or textboxes, text boxes with no information about what the user is expected to type, a haphazard organization of elements on the screen, etc. is not acceptable. In other words, you should aim higher than a "functional UI".
- The interactions must be reasonably user-friendly and intuitive. We do not expect snazzy, highly user-friendly programs. Our standard is: can a user unfamiliar with your code and technical documentation operate the program correctly without reading your code and technical documentation?
- Choose GUI elements carefully to minimize user errors whenever you can. You are not expected to create custom widgets for greater usability, but anything within Java Swing is allowed. **The provided code example shows some Swing features that you are free to use.**

#### 2.3 Text-based view

The text-based view should still work, although the new features from this assignment need not be supported in it.

### 3 Design

We expect your design to follow the MVC architecture. Adding feature logic code in the view will cost you points! A good implementation of MVC allows us to substitute one part with minimal changes to the others.

Your model and controller should have had an interface: if it did not, please add it to your design now. Your program should now have a formal view, with an interface and an implementation. This way, the controller communicates with the model and the view in a principled way.

**You are allowed to enhance or change your existing design. However we expect you to follow the SOLID principles as much as you can. When you do need to edit/enhance your design, you should document and justify the changes, both in the code and the DESIGN-README file. You will be graded on the number and extent of design changes.**

Do not compromise on your design in a quest to make a snazzy, feature-rich, polished program! A polished product may not get you any extra credit, but a poorly designed program will cost you!

### 3 Command-line arguments

Your program (from IntelliJ or the JAR file) should accept command-line inputs. Three command-line inputs are valid:

- `java -jar Program.jar -text `: when invoked in this manner the program should open with the text-based interface. This is how the program worked in the last assignment.
- `java -jar Program.jar `: when invoked in this manner the program should open the graphical user interface. This is what will happen if you simply double-click on the jar file.

Any other command-line arguments are invalid: in these cases the program should display an error message suitably and quit.