<center><H1>Laboratoire Server</H1></center>


#### Implémentation de AbstractBuffer<T>:
Pour l'implémentation de AbstractBuffer, nous avons créé une classe buffer basée sur le code fourni en annexe du cours, présent à l'adresse suivante:

http://reds.heig-vd.ch/share/cours/PCO/cours/code/5-prodcons/prodcons_bufferN_correct.tar.gz

Nous avons décidé de mettre en place des buffers de 10 requêtes dans Fileserver, même si ce nombre aurait pu être plus conséquent. Ces buffers étant alloués dynamiquement, il a également été nécessaire de bien les supprimer dans le destructeur de Fileserver.


#### Implémentation du dispatcher de requêtes:
Le dispatcher de requêtes va créer un thread par requête à traiter. Il va également garder en interne une liste des threads lancés et non terminés afin de pouvoir assurer leur bonne terminaison. Il se chargera donc de les tuer et de les supprimer.

#### Implémentation des threads workers:
Les threads workers vont créer dans leur constructeur un nouveau gestionnaire de requêtes. C'est ce dernier qui permettra d'obtenir une réponse à la requête souhaitée. Nous avons réfléchi à l'éventualité de mettre ce gestionnaire en statique pour éviter d'avoir à en créer un grand nombre, cependant tous les threads devant appeler la méthode handle, ceci reviendrait à enlever le parallélisme et donc la notion de thread.
Afin que les workers puissent transmettre la réponse au buffer de réponses, il a été nécessaire de passer son adresse par pointeur au dispatcher de requête, qui lui-même se chargera de la passer au workers pour un futur usage.

#### Comparez la performance de cette version concurrente avec celle de la version de base. Constatez-vous une amélioration ?
Nous remarquons une très nette amélioration. La première version prenait plus de trente seconde pour parvenir à répondre à une seule requête. Désormais, nous pouvons multiplier ce nombre par un facteur de 10 pour un résultat identique.

#### Que se passe-t-il lorsqu’on lance un nombre de requêtes très important (par ex. 10’000), et comment l’expliquez-vous ?
Notre programme crash. Ceci est normal car en l'état actuelle de la situation, notre dispatcher de requêtes se contente de créer un thread par requête sans pour autant limiter le nombre de threads pouvant tourner en parallèle. Nous aurons donc 10'000 threads créés, ce qui accaparera toutes les ressources de notre ordinateur jusqu'à ce que ce dernier ne soit plus capable de gérer ses ressources internes.

#### Comment pourrait-on protéger le serveur de cet effet néfaste ?
Nous allons, comme spécifié dans la seconde partie de ce laboratoire, mettre en place un thread pool. De cette façon, nous pourrons limiter le nombre de thread pouvant tourner en parallèle et éviter d'allouer plus de mémoire à notre programme que ce que notre ordinateur est capable.

Cédric Jeulin Lankeu Ngassam
Benjamin Thomas

Asvasv
