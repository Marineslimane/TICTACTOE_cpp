g++ Main.cpp Player.cpp -o main.exe
puis executer main.exe

idée : 
- add sounds
- make it psychological, add stress > inspo = squid game
- add animations, pop ups etc

> make a little story
> make it clickable instead of writing

    if (std::cin.fail() || move < 0 || move > 8) {
        std::cout << "Invalid input! Try again.\n";
        std::cin.clear();             // reset error
        std::cin.ignore(1000, '\n');  // discard bad input
    } else {
        break; // valid input
    }