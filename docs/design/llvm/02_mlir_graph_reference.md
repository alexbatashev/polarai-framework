<!-- Autogenerated by mlir-tblgen; don't manually edit -->
### `graph.add` (athena::backend::llvm::AddOp)

element-wise addition operation

The `graph.add` operation performs element-wise addition between two tensors.
The shapes of the tensor operands are expected to match.

#### Attributes:

| Attribute | MLIR Type | Description |
| :-------: | :-------: | ----------- |
`tensor_addr` | IntegerAttr | 64-bit signless integer attribute
`node_id` | IntegerAttr | 64-bit signless integer attribute
`node_name` | StringAttr | string attribute
`cluster_id` | IntegerAttr | 64-bit signless integer attribute

#### Operands:

| Operand | Description |
| :-----: | ----------- |
`lhs` | tensor of any type values
`rhs` | tensor of any type values

#### Results:

| Result | Description |
| :----: | ----------- |
&laquo;unnamed&raquo; | tensor of any type values

### `graph.alloca` (athena::backend::llvm::AllocaOp)

memory allocation operation

The `graph.alloca` operation performs memory allocation for tensor.

#### Attributes:

| Attribute | MLIR Type | Description |
| :-------: | :-------: | ----------- |
`tensor_addr` | IntegerAttr | 64-bit signless integer attribute
`node_id` | IntegerAttr | 64-bit signless integer attribute
`node_name` | StringAttr | string attribute
`cluster_id` | IntegerAttr | 64-bit signless integer attribute

#### Results:

| Result | Description |
| :----: | ----------- |
&laquo;unnamed&raquo; | tensor of any type values

### `graph.call` (athena::backend::llvm::CallOp)

call operation

The `graph.call` operation allows one to make calls to arbitrary functions outside the graph.
This is useful for loader invocation and user-defined operations.

#### Attributes:

| Attribute | MLIR Type | Description |
| :-------: | :-------: | ----------- |
`callee` | FlatSymbolRefAttr | flat symbol reference attribute
`tensor_addr` | IntegerAttr | 64-bit signless integer attribute
`node_id` | IntegerAttr | 64-bit signless integer attribute
`node_name` | StringAttr | string attribute
`cluster_id` | IntegerAttr | 64-bit signless integer attribute

#### Operands:

| Operand | Description |
| :-----: | ----------- |
`inputs` | tensor of any type values

#### Results:

| Result | Description |
| :----: | ----------- |
&laquo;unnamed&raquo; | tensor of any type values

### `graph.matmul` (athena::backend::llvm::MatmulOp)

generic matrix-matrix multiplication operation

The `graph.matmul` operation performs generic matrix-matrix multiplication of tensors.
The operands are expected to be rank 2 tensor with shapes, that allow such operation.

```
C = alpha * A * B + beta * C
```

#### Attributes:

| Attribute | MLIR Type | Description |
| :-------: | :-------: | ----------- |
`transposeA` | BoolAttr | bool attribute
`transposeB` | BoolAttr | bool attribute
`tensor_addr` | IntegerAttr | 64-bit signless integer attribute
`node_id` | IntegerAttr | 64-bit signless integer attribute
`node_name` | StringAttr | string attribute
`cluster_id` | IntegerAttr | 64-bit signless integer attribute

#### Operands:

| Operand | Description |
| :-----: | ----------- |
`lhs` | 2D tensor of any type values
`rhs` | 2D tensor of any type values
`alpha` | any type
`beta` | any type

#### Results:

| Result | Description |
| :----: | ----------- |
&laquo;unnamed&raquo; | 2D tensor of any type values

### `graph.memlock` (athena::backend::llvm::MemlockOp)

memory lock operation

The `graph.memlock` operation locks tensor in device memory
preventing it from being forced out by other memory operations.

#### Attributes:

| Attribute | MLIR Type | Description |
| :-------: | :-------: | ----------- |
`tensor_addr` | IntegerAttr | 64-bit signless integer attribute
`node_id` | IntegerAttr | 64-bit signless integer attribute
`node_name` | StringAttr | string attribute
`cluster_id` | IntegerAttr | 64-bit signless integer attribute

### `graph.memrelease` (athena::backend::llvm::MemreleaseOp)

memory release operation

The `graph.memrelease` operation marks memory region as free.

#### Attributes:

| Attribute | MLIR Type | Description |
| :-------: | :-------: | ----------- |
`tensor_addr` | IntegerAttr | 64-bit signless integer attribute
`node_id` | IntegerAttr | 64-bit signless integer attribute
`node_name` | StringAttr | string attribute
`cluster_id` | IntegerAttr | 64-bit signless integer attribute

### `graph.mul` (athena::backend::llvm::MulOp)

element-wise multiplication operation

The `graph.mul` operation performs element-wise multiplication between two tensors.
The shapes of the tensor operands are expected to match.

#### Attributes:

| Attribute | MLIR Type | Description |
| :-------: | :-------: | ----------- |
`tensor_addr` | IntegerAttr | 64-bit signless integer attribute
`node_id` | IntegerAttr | 64-bit signless integer attribute
`node_name` | StringAttr | string attribute
`cluster_id` | IntegerAttr | 64-bit signless integer attribute

#### Operands:

| Operand | Description |
| :-----: | ----------- |
`lhs` | tensor of any type values
`rhs` | tensor of any type values

#### Results:

| Result | Description |
| :----: | ----------- |
&laquo;unnamed&raquo; | tensor of any type values

### `graph.return` (athena::backend::llvm::ReturnOp)

return operation

The `graph.return` operation denotes the end of the graph.

### `graph.touch` (athena::backend::llvm::TouchOp)

Mark tensor as non-removable


#### Attributes:

| Attribute | MLIR Type | Description |
| :-------: | :-------: | ----------- |
`node_id` | IntegerAttr | 64-bit signless integer attribute
`node_name` | StringAttr | string attribute
`cluster_id` | IntegerAttr | 64-bit signless integer attribute

#### Operands:

| Operand | Description |
| :-----: | ----------- |
`tensor` | tensor of any type values
