Users with access to the file system on the installation should not be able to read the master password.
- Das Master Passwort wird jetzt auch verschlüsselt und in einem seperaten File gespeichert.

By setting a new password, it should be entered twice and checked for equality before writing to file.
- Mit der Funktion DoubleCheck in der Klasse Tools wird das sichergestellt.

As the solution was specifically developed for the very first customer, it cannot be installed on other machines. Seems that a more flexible configuration for locations of “master.pw” file and password.pw folder is required.
- Es wird jetzt ein Ordner Passwords in dem Projekt erstellt und in dem werden die einzelnen Password Files gespeichert, weiters gibt es in diesem Ordner einen extra Ordner für das Master Password.

The encryption method for the passwords should be exchangeable. Right now, the app supports only AES and there is no easy/foreseen way to introduce another algorithm. It would be great to switch between already implemented methods by proper configuration settings.
- In der CipherFacility gibt es jetzt einen zweiten Algorithmus für Encrypt und Decrypt zu verwenden.

Right now, each password is stored in a separate file. As figured out by some marketing surveys, some customers prefer storing all passwords in a single file or maybe use more advanced storage types (e.g.: databases). Introducing and exchanging storage technologies/concepts is necessary.
- Hierzu habe ich nichts implementiert.