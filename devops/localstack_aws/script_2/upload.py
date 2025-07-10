import logging
import localstack_client.session as boto3
from botocore.exceptions import ClientError
import json
import os
import mimetypes

logger = logging.getLogger()
logging.basicConfig(level=logging.INFO, format='%(asctime)s: %(levelname)s: %(message)s')

s3_client = boto3.client("s3")

def upload_file(file_name, bucket, object_name=None):
    try:
        if object_name is None:
            object_name = os.path.basename(file_name)
        response = s3_client.upload_file(
            file_name, bucket, object_name, 
            ExtraArgs={'ACL': 'public-read', 'ContentType': 'text/html'})
    except ClientError:
        logger.exception('Could not upload file to S3 bucket.')
        raise
    else:
        return response


def main():
    file_name = 'D:\Desktop\\tho_lab4\index.html'
    object_name = 'index.html'
    bucket = 'testwebsite'
    
    logger.info('Uploading file to S3 bucket in LocalStack...')
    s3 = upload_file(file_name, bucket, '{}'.format(object_name))
    logger.info('File uploaded to S3 bucket successfully.')


if __name__ == '__main__':
    main() 
