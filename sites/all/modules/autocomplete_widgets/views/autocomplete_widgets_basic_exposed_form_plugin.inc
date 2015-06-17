<?php

/**
 * @file
 * Views exposed form plugin for Autocomplete Widgets module.
 */
class autocomplete_widgets_basic_exposed_form_plugin extends views_plugin_exposed_form_basic {

  /**
   * Return a string to display as the clickable title for the control.
   */
  function summary_title() {
    return t('Autocomplete widgets');
  }

  /**
   * Declare custom plugin options.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['make_autocompletable'] = array('default' => array());
    return $options;
  }

  /**
   * Generate form elements for custom plugin options.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $relationships = $this->view->relationship;
    $options = array();
    foreach ($this->display->handler->get_handlers('filter') as $filter => $handler) {
      if ($handler->is_exposed() && $handler->content_field['widget']['module'] == 'autocomplete_widgets') {
        $options[$filter] = $handler->ui_name();
        if (!empty($handler->options['relationship'])) {
          $relationship = $handler->options['relationship'];
          if (!empty($relationships[$relationship])) {
            $options[$filter] = '('. $relationships[$relationship] .') '. $options[$filter];
          }
        }
      }
    }

    if (!empty($options)) {
      $form['make_autocompletable'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Convert into a autocomplete widget'),
        '#options' => $options,
        '#default_value' => $this->options['make_autocompletable'],
        '#description' => t('This list contains only exposed filters for CCK Text and Number fields.'),
      );
    }
  }

  /**
   * Alter the exposed filters based on plugin options.
   */
  function exposed_form_alter(&$form, &$form_state) {
    parent::exposed_form_alter($form, $form_state);

    if (!empty($this->options['make_autocompletable'])) {
      foreach ($this->options['make_autocompletable'] as $filter) {
        $field_name = $this->view->filter[$filter]->content_field['field_name'];
        $type_name = $this->view->filter[$filter]->content_field['type_name'];
        $form[$filter]['#autocomplete_path'] = 'autocomplete_widgets/'. $type_name .'/'. $field_name;
      }
    }
  }
}
