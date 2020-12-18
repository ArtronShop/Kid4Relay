Blockly.Blocks['kid4relay_set'] = {
	init: function() {
		this.jsonInit({
			"type": "kid4relay_set",
			"message0": Blockly.Msg.KID4RELAY_SET_MESSAGE,
			"args0": [{
				"type": "input_value",
				"name": "ch",
				"check": "Number"
			}, {
				"type": "input_value",
				"name": "value",
				"check": [
					"Number",
					"Boolean"
				]
			  }
			],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 225,
			"tooltip": Blockly.Msg.KID4RELAY_SET_TOOLTIP,
			"helpUrl": "https://www.ioxhop.com/p/1130"
		});
	},
	xmlToolbox: function() {
		return `
			<block type="kid4relay_set">
				<value name="ch">
					<shadow type="math_number">
						<field name="VALUE">1</field>
					</shadow>
				</value>
				<value name="value">
					<shadow type="math_number">
						<field name="VALUE">1</field>
					</shadow>
				</value>
			</block>
		`;
	}
};
