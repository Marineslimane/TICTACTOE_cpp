Si execution dans le terminal: 
    cd src
    g++ Main.cpp Player.cpp -o main.exe
    main.exe


Organisation du code :

- Player.cpp : les fonctions liées aux joueurs, qui n'utilisent quasiment que Struct Player
- Game.cpp : les fonctions pour la logique du jeu ainsi que l'affichage
- Main.cpp : démarrage

Au démarrage, dans Main.cpp, seulement start_menu() est appelée et c'est cette fonction qui appelle le mode de jeu en fonction du choix de l'utilisateur.

J'ai essayé au maximum de créer des fonctions à chaque fois qu'une portion de code se repète (à part si cela n'avait pas grand intérêt), ce qui a donné vie à de multiples fonctions en plus : winner_announcement, same_symbol_verification...


Explications supplémentaires : 

J'ai décidé de représenter le plateau de jeu board comme une matrice, array of arrays, car cela me semblait plus simple à parcourir. Cela fait que pour déterminer les coups possibles à un certain état du jeu, comme dans la fonction possible_moves, j'ai dû stocker ces cases vides dans un vector of arrays : vector car je ne connais pas à l'avance le nombre de cases vides et où les arrays sont de taille 2 et représentent les duos d'indice {i, j} des cases vides.


Améliorations : 

Mon IA de base reprend la méthode non biaisée vue en cours. Puis, mon IA améliorée utilise
l'élagage alpha-bêta. Pour cela j'ai implémenté notamment les fonctions alpha_beta_pruning et find_best_AI_move en me basant sur la description de l'algorithme donnée sur Wikipedia et sur mes souvenirs de Prépa. Grâce à cet algorithme, mon IA ne peut que gagner ou faire des matchs nuls. 


Problèmes rencontrés et solutions trouvées : 

J'ai notamment eu des problèmes par rapport à :
- Ce que renvoie ma fonction test_victory car l'information que j'obtiens sur le gagnant est son symbole or, je voulais renvoyer son nom. Pour y remédier, j'ai créé la fonction symbol_to_name dans Player.cpp qui permet d'accèder au nom du joueur à partir de son symbole

- La vérification de la validité des input et particulièrement de ceux des indices pour jouer un coup car je devais redemander à l'utilisateur de faire des input tant que les indices saisis ne correspondait pas à une case vide. Or, avec un appel récursif de la fonction player_move j'obtenais des symboles incohérents car le coup, même impossible, était joué quand même. Pour y remédier, j'ai rajouté un return; après l'appel récursif comme cela l'execution de la fonction s'arrête avant que le coup impossible soit joué

- L'obtention d'un index random dans unbiased_random_move car je travaille avec empty_squares.size() qui n'est pas de type int du coup j'ai dû faire une conversion en int avec static_cast<int>. De même pour la conversion des input des indices : les input devaient être des int pour pouvoir les utiliser en tant qu'indices dans le array of arrays mais je devais également vérifier qu'ils étaient bien valides (0 < i, j <= 2) et pour cela je les recevais en tant que std::string avec std::getline(std::cin, line) du coup j'ai dû convertir le premier charactère de line, line[0] en int pour obtenir mon indice sous le bon type (column = line[0] - '0')


Note : Le mode IA par défaut est celui amélioré. Pour pouvoir jouer avec le mode IA simple, sans améliorations, il faut modifier le code dans le switch() de start_menu dans Game.cpp.