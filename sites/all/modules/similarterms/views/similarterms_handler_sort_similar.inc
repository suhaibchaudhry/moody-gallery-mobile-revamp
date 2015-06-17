<?php

class similarterms_handler_sort_similar extends views_handler_sort {
  
  function option_definition() {
    $options = parent::option_definition();

    $options['order'] = array('default' => 'DESC');

    return $options;
  }

  function query() {
    // Check whether it's views3 or views2.
    if (version_compare(views_api_version(), '3.0-alpha1', '>=')) {
      $params = array(
        'function' => 'count',
      );

      // Add a COUNT(nid) and sort by it.
      $this->query->add_orderby('node', 'nid', $this->options['order'], NULL, $params);
    }
    else {
      // add function to count nid occurrences based on grouping
      $this->query->add_field(NULL, 'COUNT(node.nid)', 'node_count', array('aggregate' => TRUE));

      // sort 'em
      $this->query->add_orderby(NULL, NULL, $this->options['order'], 'node_count');

      // group 'em
      $this->query->add_groupby('nid');
    }
  }

}
