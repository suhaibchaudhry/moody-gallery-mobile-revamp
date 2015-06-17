<?php

function storm_drush_command() {
  $items['storm-reinstall'] = array(
    'description' => dt('Disable, Uninstall, Reinstall storm modules in the correct order, in one cmd.'),
    'examples' => array(
      'drush storm-reinstall' => 'Disable, Unistall, and Reinstall Storm & sub modules'
    ),
  'aliases' => array('stre'),
  );
  return $items;
}

function drush_storm_reinstall() {
  $sub_mods = array(
    'stormexpense',
    'storminvoice',
    'stormnote',
    'stormorganization',
    'stormperson',
    'stormproject',
    'stormtask',
    'stormteam',
    'stormticket',
    'stormtimetracking');

  drush_invoke_process(@self, 'pm-disable', array('storm'));

  drush_invoke_process(@self, 'pm-uninstall', array('stormexpense', 'storminvoice', 'stormnote', 'stormteam', 'stormtimetracking'));

  drush_invoke_process(@self, 'pm-uninstall', array('stormperson', 'stormticket'));

  drush_invoke_process(@self, 'pm-uninstall', array('stormtask'));

  drush_invoke_process(@self, 'pm-uninstall', array('stormproject'));

  drush_invoke_process(@self, 'pm-uninstall', array('stormorganization'));

  drush_invoke('pm-enable', $sub_mods);
}

