coalliance_foxml_migration
==========================

migrating from Islandora 6 to Islandora 7


A drush script to ingest a FoxML record exported from Islandora 6 into Islandora 7 using Tuque.

was broken because of access restrctions  ( error at https://gist.github.com/edf/12a8fda112a51661bba7 )

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

drush -u 1 migrate_foxml2 ~/wyu_9306.foxml wyu wyu:9306

drush foxml_save_pids_for_namespace wyu



Thanks to: https://github.com/Islandora/islandora/wiki/Working-With-Fedora-Objects-Programmatically-Via-Tuque
