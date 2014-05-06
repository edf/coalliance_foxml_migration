coalliance_foxml_migration
==========================

migrating from Islandora 6 to Islandora 7


A broken drush script to ingest a FoxML record exported from Islandora 6 into Islandora 7 using Tuque.

see error at https://gist.github.com/edf/12a8fda112a51661bba7

Dependencies
------------
The Islandora module.

Installation
------------
Clone this module into your modules folder.  Then enable using either Drupal's admin interface or Drush.

* $ cd /var/www/html/drupal7/sites/YourSiteHere/modules
* $ git clone https://github.com/edf/coalliance_foxml_migration.git
* $ drush en coalliance_foxml_migration

Logging
-------
use "drush ws --tail --full" to tail the watchdog logs

Usage
----



Thanks to: https://github.com/Islandora/islandora/wiki/Working-With-Fedora-Objects-Programmatically-Via-Tuque
