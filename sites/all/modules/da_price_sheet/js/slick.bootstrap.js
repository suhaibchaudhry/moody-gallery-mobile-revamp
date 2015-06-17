Drupal.behaviors.gridGenerate = function() {
  function CurrencyFormatter(row, cell, value, columnDef, dataContext) {
	if(value == null || value === "") {
      return "-";
    } else {
      return "<span style='color:green;font-weight:bold;'>$" + parseFloat(value).toFixed(2) + "</span>";
    }
  }
  
  function nodeIDFormatter(row, cell, value, columnDef, dataContext) {
	if(value == null || value === "") {
      return "-";
    } else {
      return '<a href="'+Drupal.settings.basePath+'node/'+ value +'" target="_blank">' + value + '</a>';
    }
  }
  
  function requiredFieldValidator(value) {
    if (value == null || value == undefined || !value.length) {
      return {valid: false, msg: "This is a required field"};
    } else {
      return {valid: true, msg: null};
    }
  }
  
  function requredCurrencyValidator(value) {
	 if (value == null || value == undefined || !value.length || isNaN(value)) {
      return {valid: false, msg: "This is a required field"};
    } else {
      return {valid: true, msg: null};
    }
  }

  $(window).load(function() {
	  var grid;
	  var data = [];
	  var columns = [
	    {id: "nid", name: "ID", field: "nid", width: 60, formatter: nodeIDFormatter},
		{id: "model", name: "Model #", field: "model", width: 100, editor: Slick.Editors.Text, validator: requiredFieldValidator},
	    {id: "title", name: "Title", field: "title", width: 200, editor: Slick.Editors.Text, validator: requiredFieldValidator},
	 	{id: "list_price", name: "List Price", field: "list_price", width: 100, editor: Slick.Editors.Text, formatter: CurrencyFormatter, validator: requredCurrencyValidator},
	    {id: "cost", name: "Cost", field: "cost", width: 100, editor: Slick.Editors.Text, formatter: CurrencyFormatter, validator: requredCurrencyValidator},
	   	{id: "sell_price", name: "Sell Price", field: "sell_price", width: 100, editor: Slick.Editors.Text, formatter: CurrencyFormatter, validator: requredCurrencyValidator}
	  ];

	 var options = {
		editable: true,
		enableAddRow: false,
		enableCellNavigation: true,
		asyncEditorLoading: false,
		autoEdit: false,
		editCommandHandler: queueAndExecuteCommand
	};

	var commandQueue = [];

	function queueAndExecuteCommand(item, column, editCommand) {
		//commandQueue.push(editCommand);
		//editCommand.execute();
		editCommand.execute();
		//makeActiveCellNormal();
		$.post(Drupal.settings.basePath+'admin/store/price-sheet/edit-callback', item, function(data) {
			//console.log(data);
		});
	}

	grid = new Slick.Grid("#price-sheet-grid", Drupal.settings.price_sheet_products, columns, options);
  });
}