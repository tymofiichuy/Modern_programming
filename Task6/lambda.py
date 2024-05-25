import boto3

def lambda_handler(event, context):
    s3 = boto3.resource('s3')
    source = 's3-start'
    destination = 's3-finish'
    key = event['Records'][0]['s3']['object']['key']
    copy_object = {'Bucket':source,'Key':key}
    s3.meta.client.copy(copy_object, destination, key)
    return {
        'statusCode': 200
    }