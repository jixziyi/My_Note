# SQL Server异常处理


``` SQL
CREATE PROCEDURE [dbo].[XXXX_SP] @xtype varchar(20) = ''
AS

DECLARE @msg varchar(500)
-- ----------------------------------
BEGIN TRY
BEGIN TRANSACTION

IF @xtype = 'type'
BEGIN
	--((EXP(SUM(LOG(ABS(IsNull(WK5, 0)))))
END


COMMIT TRANSACTION
END TRY
BEGIN CATCH
IF @@TRANCOUNT > 0
BEGIN
	 ROLLBACK TRANSACTION
END
	SET @msg = ERROR_MESSAGE() + ' [' + ERROR_PROCEDURE() + ':' + Convert(varchar,ERROR_LINE()) + ']'  
	RAISERROR (@msg, 16, 1) WITH NOWAIT
	INSERT INTO log_errors
	SELECT '', ERROR_PROCEDURE(), ERROR_LINE(), ERROR_MESSAGE(), getdate()
END CATCH
```