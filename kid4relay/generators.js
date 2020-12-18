Blockly.JavaScript['kid4relay_set'] = function(block) {
	var value_ch = Blockly.JavaScript.valueToCode(block, 'ch', Blockly.JavaScript.ORDER_ATOMIC);
	var value_value = Blockly.JavaScript.valueToCode(block, 'value', Blockly.JavaScript.ORDER_ATOMIC);

	var code = `DEV_I2C1.Kid4Relay(0, 0x39).set(${value_ch}, ${value_value});\n`;
	return code;
};
