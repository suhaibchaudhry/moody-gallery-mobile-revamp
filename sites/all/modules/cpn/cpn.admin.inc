<?php

/**
 * Settings form.
 */
function cpn_settings() {
  $options[0] = t('None');

  if (is_file('sites/all/libraries/codemirror/js/codemirror.js')) {
    $options['codemirror'] = 'Code Mirror';
  }

  $form['cpn_syntax_highlighting'] = array(
    '#title' => t('Syntax Highlighting'),
    '#type' => 'radios',
    '#options' => $options,
    '#default_value' => variable_get('cpn_syntax_highlighting', 0),
  );

  return system_settings_form($form);
}
